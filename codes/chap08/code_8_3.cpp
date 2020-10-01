// ノード p の直後にノード v を挿入する
void insert(Node* v, Node* p) {
    v->next = p->next;
    p->next = v;
}
