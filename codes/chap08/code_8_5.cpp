struct Node {
    Node *prev, *next;
    string name; // ノードに付随している値

    Node(string name_ = "") :
    prev(NULL), next(NULL), name(name_) { }
};
