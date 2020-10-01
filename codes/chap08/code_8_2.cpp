struct Node {
    Node* next; // 次がどのノードを指すか
    string name; // ノードに付随している値

    Node(string name_ = "") : next(NULL), name(name_) { }
};
