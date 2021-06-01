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

    static DirectedNode* Build(I&& i) { return BaseNode<I>::template Allocate<DirectedNode>(std::forward<I>(i)); }

    DirectedNode* next;
};

template<typename I>
struct BiDirectionalNode : BaseNode<I> {
    BiDirectionalNode(I&& t)
        : BaseNode<I>(std::forward<I>(t)), next{}, prev{} {}
    ~BiDirectionalNode() override {}
    
    static BiDirectionalNode* Build(I&& i) { return BaseNode<I>::template Allocate<BiDirectionalNode>(std::forward<I>(i)); }

    BiDirectionalNode* next;
    BiDirectionalNode* prev;
};