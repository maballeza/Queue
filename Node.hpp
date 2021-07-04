#define BUILD
#define HANDLE

#ifdef HANDLE
template<typename N>
struct HNode {
    HNode(N* n) : Node{ n } {};
    HNode(HNode&& hn);
    ~HNode() { delete Node; Node = nullptr; }
    N* Release() { N* ret{ Node }; Node = nullptr; return ret; }
    N* Node;
    N& operator*() { return *Node; }
    N* operator->() { return Node; }
};
#endif

template<typename I>
struct BaseNode {
    I item;
    virtual ~BaseNode() {}
protected:
    BaseNode(I&& t) : item{ t } {}

    template<class N>
    static N* Allocate(I&& i) { return new N{ std::move(i) }; }
};

template<typename I>
struct DirectedNode : BaseNode<I> {
    DirectedNode(I&& t)
        : BaseNode<I>(std::forward<I>(t)), next{} {}
    DirectedNode(DirectedNode&& dn) noexcept
        : BaseNode<I>(std::forward<I>(dn.item)), next{ dn.next } {
        dn.item = I{};
        dn.next = nullptr;
    }
    ~DirectedNode() override {}

    DirectedNode* next;

protected:
    static DirectedNode* Build(I&& i) { return BaseNode<I>::template Allocate<DirectedNode>(std::forward<I>(i)); }
};

template<typename I>
struct BiDirectionalNode : BaseNode<I> {
    BiDirectionalNode(I&& t)
        : BaseNode<I>(std::forward<I>(t)), next{}, prev{} {}
    ~BiDirectionalNode() override {}

    BiDirectionalNode* next;
    BiDirectionalNode* prev;

protected:
    static BiDirectionalNode* Build(I&& i) { return BaseNode<I>::template Allocate<BiDirectionalNode>(std::forward<I>(i)); }
};

#ifdef BUILD
template<typename N>
struct Build : N {
    template<typename I>
    static HNode<N> Instance(I&& i) { return HNode<N>{ typename N::Build(std::forward<I>(i))}; }
};
#endif
