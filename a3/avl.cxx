
#include <cstddef>
#include <iostream>

namespace avl {
    template<typename Y>
    class tree {
    public:
        class node;
        using node_p = node*;

        class node {
        public:
            Y data{};
            size_t count{1};
            int balance{0};
            node_p left{nullptr};
            node_p right{nullptr};

            node(const Y& v)
                : data{v}
            {}

            static node_p create(const Y& v)
            {
                return new node(v);
            }
        };

    public:
        tree() {}
        ~tree() {}

        using value_type = Y;

        tree& add(const Y& v)
        {
            bool h = false;
            add(v, _root, h);
            return *this;
        }

    private:
        void add(const Y& v, node_p& r, bool& h)
        {
            if( r == nullptr ) {
                r = node::create(v);
                h = true;
            }
            else {
                if( v < r->data ) {
                    add(v, r->left, h);
                    if( h ) {
                        if( -1 == r->balance ) {                            
                            r->balance = 0;
                            h = false;
                        }
                        else if( 0 == r->balance )
                            r->balance = 1;
                        else {
                            auto rl = r->left;
                            if( 1 == rl->balance ) {
                                r->left = rl->right;
                                rl->right = r;
                                r->balance = 0;
                                r = rl;
                            }
                            else if( -1 == rl->balance ) {
                                auto rlr = rl->right;
                            }
                            h = false;
                        }
                    }
                }
                else if( v > r->data ) {
                    add(v, r->right, h);
                    if( h ) {
                        if( 1 == r->balance ) {
                            r->balance = 0;
                            h = false;
                        }
                        else if( 0 == r->balance )
                            r->balance = -1;
                        else {
                            std::cout << "R: " << (r->balance) << std::endl;
                            // rebalance
                        }
                    }
                }
                else
                    r->count += 1;
            }
        }

    private:
        node_p _root{nullptr};
    };
}


int main()
{
    avl::tree<int> t0;
    t0.add(20).add(12).add(8);

    return 0;
}
