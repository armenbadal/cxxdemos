#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <uriparser/Uri.h>


class Uri {
public:
    explicit Uri(std::string_view src)
        : source_{src}
    {
        try {
            parse();
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::string toString() const
    {
        std::ostringstream oss;
        oss << scheme_ << "://" << host_;
        if(!port_.empty()) { 
            oss << ":" << port_;
        }
        for(auto& p : path_) {
            oss << '/' << p;
        }
        if(!query_.empty()) {
            oss << '?';
            for(auto& [k, c, v] : query_) {
                oss << k;
                if(c != '\0') {
                    oss << '=';
                }
                if(!v.empty()) {
                    oss << v;
                }
                oss << '&';
            }
        }
        auto res = oss.str();
        res.pop_back();
        return res;
    }

private:
    void parse()
    {
        UriUriA ur;
        const char* errPos = nullptr;
        if(URI_SUCCESS != uriParseSingleUriA(&ur, source_.data(), &errPos)) {
            throw std::runtime_error{"Bad URI."};
        }

        scheme_ = stringView(ur.scheme);
        host_ = stringView(ur.hostText);
        port_ = stringView(ur.portText);

        // path
        pathSegments(ur.pathHead);

        // query
        splitQuery(ur.query);

        uriFreeUriMembersA(&ur);
    }

    void pathSegments(UriPathSegmentA* psh)
    {
        for(auto* ip = psh; ip != nullptr; ip = ip->next) {
            path_.push_back(stringView(ip->text));
        }
    }

    void splitQuery(UriTextRangeA& utr)
    {
        const char* qi = utr.first;
        const char* const end = utr.afterLast;
        while(qi < end) {
            const char* p = qi;
            while(*p != '&' && p != end) {
                ++p;
            }

            const char* ki = qi;
            while(*ki != '=' && ki < p) {
                ++ki;
            }
            std::string_view key(qi, ki - qi);
            char sep = '\0';
            if(*ki == '=') {
                sep = '=';
                ++ki;
            }
            std::string_view value(ki, p - ki);
            query_.push_back({key, sep, value});
            
            qi = p + 1;
        }
    }

    static std::string_view stringView(UriTextRangeA& utr)
    {
        return std::string_view(utr.first, utr.afterLast - utr.first);
    }

private:
    std::string source_;

    std::string_view scheme_;
    std::string_view host_;
    std::string_view port_;
    std::vector<std::string_view> path_;
    std::vector<std::tuple<std::string_view, char, std::string_view>> query_;
    std::string_view fragment_;
};




int main()
{
    const std::string s = "https://www.youtube.com/watch?v=1q_qrobPmKE&one&k=myau&two=";
    std::cout << s << std::endl;
    Uri u{s};
    std::cout << u.toString() << std::endl;
    std::cout << "Ok\n";
}
