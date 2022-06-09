#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct Node {
    struct Node* left_child;
    struct Node* right_siblings;
    char data;
    int level;
    char parent;

}Node;

typedef struct Tree {
    Node* root;
    int count;
    int binary;
}Tree;

Node* CreateNode(char NewData);
void __init__(Tree* my_tree);
Node* search(Tree* my_tree, Node* node, char data);
void PreOrderPrintTree(Tree* my_tree, Node* node);
void create(Tree* my_tree, char data);
void insert_node(Tree* my_tree, char p_node, char c_list[]);
void get_sibling(Tree* my_tree, char data, Node* node);
char get_parent(Tree* my_tree, char data);
void get_child(Tree* my_tree, Node* node, char data);
int level_of_node(Tree* my_tree, char data);
int level_of_tree(Tree* my_tree, Node* node);
void delete_node(Tree* my_tree, Node* node, char data);
void get_ancestors(Tree* my_tree, char data);
void get_descendants(Tree* my_tree, char data);
int degree_of_node(Tree* my_tree, Node* node, char data);
int degree_of_tree(Tree* my_tree, Node* node);
int count_node(Tree* my_tree);
void join_trees(char data, Tree* my_tree1, Tree* my_tree2);
void insert_sibling(Tree* my_tree, char data, char c_list[]);
void give_level(Tree* my_tree, Node* node);
void clear(Tree* my_tree, Node* node);

int main() {

    Tree my_tree;
    Tree my_tree2;
    __init__(&my_tree);
    __init__(&my_tree2);

    char nodes[5] = { 'V', 'X', 'Y' };
    char new_node[5] = { 'Z' };
    //making tree2 for join tree ADT
    create(&my_tree2, 'U');
    insert_node(&my_tree2, 'U', nodes);
    insert_node(&my_tree2, 'V', new_node);



    int i = 0;
    int Flag = 1;
    int com_index = 0;
    
    printf("ťçżëŔÚ Ăß°Ą ÇÔźö 1: search(), ĂŁ°íŔÚÇĎ´Â ľĽŔĚĹÍ¸Ś °Ž°íŔÖ´Â łëľĺ¸Ś šÝČŻÇŘÁÖ´Â ÇÔźöŔĚ´Ů.\n");
    printf("ťçżëŔÚ Ăß°Ą ÇÔźö 2: get left child() ¸íˇÉžî: F()\n");
    printf("ťçżëŔÚ Ăß°Ą ÇÔźö 3: get right child() ¸íˇÉžî: H()\n");
    printf("join trees()´Â ąâÁ¸żĄ ¸¸ľéžîÁŽ ŔÖ´Â my_tree2¸Ś ťçżëŔÚ°Ą ¸¸ľç ĆŽ¸ŽżÍ ÇŐÄĄ´Â °úÁ¤ŔÔ´Ď´Ů. ¸íˇÉžî: J(_)\n");
    printf("¸íˇÉžîżĄ °řšéŔĚ žřľľˇĎ Ăł¸ŽÇŘÁÖźźżä\n");
    printf("\n źąĹĂ: ŔĚÁřĆŽ¸ŽˇÎ ÇŇˇÁ¸é 1Ŕť ŔÔˇÂÇĎ°í, ŔĎšÝĆŽ¸Ž´Â 0Ŕť ŔÔˇÂÇŘÁÖźźżä\n");
    scanf_s("%d", &my_tree.binary);
    getchar();//šöĆŰÁŚ°Ĺ
    if (my_tree.binary == 1) {
        printf("ŔĚÁř ĆŽ¸ŽˇÎ ą¸ÇöľË´Ď´Ů.\n");
    }
    else {
        printf("ŔĎšÝĆŽ¸ŽˇÎ ą¸ÇöľË´Ď´Ů.");
    }
    while (Flag) {
        char com[20] = { 0, };
        char c_list[10] = { 0, };
        printf("\n¸íˇÉŔť ŔÔˇÂÇĎźźżä: ");
        fgets(com, sizeof(com), stdin);

        for (com_index = 0; com_index < 20; com_index++) {
            i = 0;

            if (com[com_index] == '\0') break;

            else if (com[com_index] == '+' && com[com_index + 1] == '^') {
                create(&my_tree, com[com_index + 2]); //create()
            }

            else if (com[com_index] == '+' && com[com_index + 2] == '(') {
                if (com[com_index - 1] == '=') {//insert_sibling
                    for (com_index = 3; com_index < 20; com_index++) {
                        if (com[com_index] >= 65 && com[com_index] <= 90) {
                            c_list[i] = com[com_index];
                            i++;
                        }
                    }
                    insert_sibling(&my_tree, com[2], c_list);
                }
                else {
                    for (com_index = 2; com_index < 20; com_index++) {
                        if (com[com_index] >= 65 && com[com_index] <= 90) {
                            c_list[i] = com[com_index];
                            i++;
                        }
                    }
                    insert_node(&my_tree, com[1], c_list);
                }
            }//insert()

            else if (com[com_index] == 'S' && com[com_index + 1] == '(') {
                get_sibling(&my_tree, com[com_index + 2], my_tree.root);
            }//get_sibling()

            else if (com[com_index] == 'P' && com[com_index + 1] == '(') {
                char getparent = get_parent(&my_tree, com[com_index + 2]);
                printf("%c\n", getparent);
            }//get_parent()

            else if (com[com_index] == 'C' && com[com_index + 1] == '(') {
                get_child(&my_tree, my_tree.root, com[com_index + 2]); //get_child()
            }

            else if (com[com_index] == 'L') {
                if (com[com_index + 1] == '(') {
                    int level_node = level_of_node(&my_tree, com[com_index + 2]);//level_of_node()
                    printf("%d\n", level_node);
                }
                else {
                    int level_tree = level_of_tree(&my_tree, my_tree.root) - 1;//level_of_tree()
                    printf("%d\n", level_tree);
                }
            }

            else if (com[com_index] == '-') {
                delete_node(&my_tree, my_tree.root, com[com_index + 1]);
            }

            else if (com[com_index] == 'A' && com[com_index + 1] == '(') {
                get_ancestors(&my_tree, com[com_index + 2]);
            }

            else if (com[com_index] == 'D' && com[com_index + 1] == '(') {
                get_descendants(&my_tree, com[com_index + 2]);//get_descendents()
            }

            else if (com[com_index] == 'G' && com[com_index + 1] == '(') {
                int dgr = degree_of_node(&my_tree, my_tree.root, com[com_index + 2]);
                printf("%d\n", dgr);//degree_of_node()
            }

            else if (com[com_index] == 'G' && com_index == 0) {
                int dgrtree = degree_of_tree(&my_tree, my_tree.root);
                printf("%d\n", dgrtree);
            }

            else if (com[com_index] == '#') {
                int counting = count_node(&my_tree);
                printf("%d\n", counting);
            }

            else if (com[com_index] == 'J' && com[com_index + 1] == '(') {
                PreOrderPrintTree(&my_tree2, my_tree2.root);
                join_trees(com[com_index + 2], &my_tree, &my_tree2);
            }

            else if (com[com_index] == 'K') {
                clear(&my_tree, my_tree.root);
            }

            else if (com[com_index] == 'T') break;
            else if (com[0] == 'Q') {
                Flag = 0;
                break; //ÇÁˇÎą×ˇĽ Ážˇá
            }
        }//for()
        if (com[0] == 'Q') printf("ÇÁˇÎą×ˇĽŔť ÁžˇáÇŐ´Ď´Ů.\n");
        else if (com[0] == 'T') {
            printf("(");
            PreOrderPrintTree(&my_tree, my_tree.root);
            if (my_tree.binary) printf(")");
        }
        else {
            printf("(");
            PreOrderPrintTree(&my_tree, my_tree.root);
            if (my_tree.binary) printf(")");
        }

    }//while()
    return 0;
}

Node* CreateNode(char NewData) {
    Node* NewNode = (Node*)malloc(sizeof(Node));
    NewNode->left_child = NULL;
    NewNode->right_siblings = NULL;

    NewNode->data = NewData;
    NewNode->level = 0;
    NewNode->parent = NULL;
    return NewNode;
}

void __init__(Tree* my_tree) {
    my_tree->root = CreateNode(NULL);
    my_tree->count = 0;
    my_tree->binary = 0;
}

Node* search(Tree* my_tree, Node* node, char data) { //ok
    if (!node) {
        return NULL;
    }
    if (node->data == data) {
        return node;
    }
    Node* leftchild = search(my_tree, node->left_child, data);
    if (leftchild != NULL) return leftchild;
    Node* rightsiblings = search(my_tree, node->right_siblings, data);
    if (rightsiblings != NULL) return rightsiblings;

}

void PreOrderPrintTree(Tree* my_tree, Node* node) { //ok
    if (!node) { //šćžîÄÚľĺ
        return;
    }
    if (!(my_tree->binary)) {//ŔĎšÝ ĆŽ¸Ž
        printf("%c ", node->data);

        if (node->left_child != NULL) {
            printf("(");
        }
        PreOrderPrintTree(my_tree, node->left_child);

        if (node->right_siblings == NULL) {
            printf(")");
        }
        PreOrderPrintTree(my_tree, node->right_siblings);
    }
    else {//ŔĚÁřĆŽ¸Ž
        printf("%c", node->data);
        if (node->left_child != NULL || node->right_siblings != NULL) printf("(");
        if (node->left_child != NULL) PreOrderPrintTree(my_tree, node->left_child);
        if (node->left_child != NULL || node->right_siblings != NULL) printf(",");
        if (node->right_siblings != NULL) PreOrderPrintTree(my_tree, node->right_siblings);
        if (node->left_child != NULL || node->right_siblings != NULL) printf(")");
    }
}

void create(Tree* my_tree, char data) { //ok
    my_tree->root->data = data;
    my_tree->count++;
}

void insert_node(Tree* my_tree, char p_node, char c_list[]) { //ok

    Node* parent = search(my_tree, my_tree->root, p_node);
    if (parent == NULL) {

        printf("error\n");
        return;
    }
    if (!(my_tree->binary)) {
        for (int i = 0; i < strlen(c_list); i++) {
            Node* new = CreateNode(c_list[i]);
            if (parent->left_child == NULL) {
                new->parent = p_node;
                parent->left_child = new;

            }
            else {
                Node* leftchild = parent->left_child;
                while (leftchild->right_siblings != NULL)
                {
                    leftchild = leftchild->right_siblings;
                }
                leftchild->right_siblings = new;
                new->parent = p_node;
            }
            my_tree->count++;
        }
        give_level(my_tree, my_tree->root);
    }
    else {
        if (strlen(c_list) > 2) {
            printf("Error: ŔĚÁřĆŽ¸ŽŔÇ ĂÖ´ë ŔÚ˝ÄŔÇ źö´Â 2ŔÔ´Ď´Ů.\n");
            return;
        }
        for (int i = 0; i < strlen(c_list); i++) {
            Node* new = CreateNode(c_list[i]);
            if (parent->left_child == NULL) {
                new->parent = p_node;
                parent->left_child = new;

            }
            else if(parent->right_siblings == NULL) {
                parent->right_siblings = new;
                new->parent = p_node;
            }
            else {
                printf("Error: ŔĚšĚ ŔÚ˝Äłëľĺ°Ą °Ąľć Â÷ ŔÖ˝Ŕ´Ď´Ů.\n");
                return;
            }
            my_tree->count++;
        }
    }
}

void insert_sibling(Tree* my_tree, char data, char c_list[]) { //ok
    char parent_data = get_parent(my_tree, data);
    insert_node(my_tree, parent_data, c_list);

}

char get_parent(Tree* my_tree, char data) { //ok

    Node* cur = search(my_tree, my_tree->root, data);
    char Parent_data = cur->parent;

    return Parent_data;
}

void get_sibling(Tree* my_tree, char data, Node* node) { //ok
    if (!(my_tree->binary)) {//ŔĎšÝĆŽ¸Ž
        printf("{");
        //Node* cur = search(my_tree, my_tree->root, data);
        char s_list[10] = { 0, };
        if (!node) {
            return;
        }
        int i = 0;
        char parent_data = get_parent(my_tree, data);
        Node* Parent = search(my_tree, my_tree->root, parent_data);
        Node* leftchild = Parent->left_child;
        while (leftchild->right_siblings != NULL) {
            if (leftchild->data != data) {
                s_list[i] = leftchild->data;
                i++;
            }
            leftchild = leftchild->right_siblings;
        }
        s_list[i] = leftchild->data;
        for (int j = 0; j < strlen(s_list); j++) {
            printf("%c ", s_list[j]);
        }

        printf("}\n");
    }
    else {//ŔĚÁřĆŽ¸Ž
        char parent_data = get_parent(my_tree, data);
        Node* parent = search(my_tree, my_tree->root, parent_data);
       
        if ((data == parent->left_child->data) && (parent->right_siblings != NULL)) {
            printf("{%c}", parent->right_siblings->data);
        }
        else if (data == parent->right_siblings) {
            printf("{%c}", parent->left_child->data);
        }
        else {
            printf("No siblings\n");
        }
    }
}

void get_child(Tree* my_tree, Node* node, char data) { //ok
    if (!node) {
        return NULL;
    }
    char c_list[10] = { 0, };
    Node* Parent = search(my_tree, my_tree->root, data);
    if (!(my_tree->binary)) {//ŔĎšÝ ĆŽ¸Ž
        Node* child = Parent->left_child;
        int i = 0;
        while (child->right_siblings != NULL) {
            c_list[i] = child->data;
            child = child->right_siblings;
            i++;
        }
        c_list[i] = child->data;
        printf("{");
        for (int j = 0; j < strlen(c_list); j++) {
            printf("%c ", c_list[j]);
        }
        printf("}\n");
    }
    else {//ŔĚÁřĆŽ¸Ž
        printf("{");
        if (Parent->left_child) printf("%c ", Parent->left_child->data);
        if (Parent->right_siblings) printf("%c", Parent->right_siblings->data);
        printf("}\n");
    }
}

int level_of_node(Tree* my_tree, char data) { //ok
    Node* cur = search(my_tree, my_tree->root, data);
    int cur_level = cur->level;
    return cur_level;
}

int level_of_tree(Tree* my_tree, Node* node) {//ok
    if (node == NULL)
        return 0;
    else if(!(my_tree->binary))//ŔĎšÝĆŽ¸Ž
    {
        
        /* compute the height of each subtree */
        int l_level = level_of_tree(my_tree, node->left_child) + 1;
        int r_level = level_of_tree(my_tree, node->right_siblings);//ŔĚÁřĆŽ¸ŽżĄź­´Â żŠąâľľ + 1

        /* use the larger one */
        
        //return(l_level + 1);
        //ľÎšřÂ° °ĄÁö°Ą ´ő łôŔť ś§ °íˇÁ
        return MAX(l_level, r_level);
    }
    else {//ŔĚÁřĆŽ¸Ž
        int lheight = level_of_tree(my_tree, node->left_child);
        int rheight = level_of_tree(my_tree, node->right_siblings);
        if (lheight > rheight)
            return(lheight + 1);
        else return(rheight + 1);
    }
}

void delete_node(Tree* my_tree, Node* node, char data) { //ok
    //´Ü¸ťłëľĺŔÎÁö ČŽŔÎ
    if (!(my_tree->binary)) {//ŔĎšÝĆŽ¸Ž
        Node* cur = search(my_tree, my_tree->root, data);
        if (cur->left_child != NULL) {
            printf("´Ü¸ťłëľĺ°Ą žĆ´Ďžîź­ ťčÁŚÇŇ źö žř˝Ŕ´Ď´Ů.\n");
            return;
        }
        //şť°Ý Áöżěąâ
        if (cur == my_tree->root) {
            my_tree->root->data = NULL;
            my_tree->root->left_child = NULL;
            printf("şó ĆŽ¸Ž ŔÔ´Ď´Ů.\n");
            return;
        }
        else {
            Node* parent_node;
            parent_node = search(my_tree, my_tree->root, get_parent(my_tree, data));
            if (cur->right_siblings != NULL) {//Ăššř¤żÍ Áß°ŁŔÇ °ÍŔť Áöżďś§
                Node* parent_node;
                parent_node = search(my_tree, my_tree->root, get_parent(my_tree, data));
                Node* leftchild = parent_node->left_child;
                if (cur == leftchild) {//ĂššřÂ° °ÍŔť ťčÁŚ
                    parent_node->left_child = cur->right_siblings;
                }
                else {//Áß°ŁŔÇ °Í
                    while (leftchild->right_siblings != cur) {
                        leftchild = leftchild->right_siblings;
                    }
                    leftchild->right_siblings = cur->right_siblings;
                }
            }
            else { //¸Ç ¸śÁö¸ˇ °ÍŔť ťčÁŚ
                cur->data = NULL;
                Node* leftchild = parent_node->left_child;
                if (leftchild->right_siblings != NULL) {
                    while (leftchild->right_siblings != cur) {
                        leftchild = leftchild->right_siblings;
                    }
                    leftchild->right_siblings = NULL;
                }
                else {
                    parent_node->left_child = NULL;
                }
            }
            free(cur);
            my_tree->count--;
        }
    }
    else {//ŔĚÁřĆŽ¸Ž
        Node* parent, * child, * suc, * suc_p, * t;

        // data¸Ś °Ž´Â łëľĺ t¸Ś Ĺ˝ťöÇŃ´Ů. parent´Â tŔÇ şÎ¸đłëľĺ´Ů.
        parent = NULL; // ˝ĂĂĘ°Ą ľÇ´Â rootŔÇ şÎ¸đ´Â žř´Ů.
        t = search(my_tree, my_tree->root, data);
        char parent_data = get_parent(my_tree, data);
        parent = search(my_tree, my_tree->root, parent_data);

        

        // Ĺ˝ťöŔĚ łĄł­ ˝ĂÁĄżĄź­ ¸¸žŕ Ĺ° °ŞŔĚ ĆŽ¸ŽżĄ žřžú´Ů¸é t´Â NULLŔĎ °ÍŔĚ´Ů.
        if (!t)
        {
            printf("Error : data is not in the tree\n");
            return; // żřÇĎ´Â °ŞŔĚ žřŔ¸šÇˇÎ return ÇŃ´Ů.
        }
        // Ŕ§żĄź­ Ĺ˝ťöŔť ¸řÇßŔť °ćżě¸Ś ´Ůˇđąâ ś§šŽżĄ ŔĚ žĆˇĄşÎĹÍ´Â Ĺ˝ťöŔĚ
        // źş°řŔűŔ¸ˇÎ ŔĚˇçžîÁł´Ů´Â °ĄÁ¤ ÇĎżĄ °ćżěŔÇ źö¸Ś ľűÁř´Ů.

        // Ăš šřÂ°: ´Ü¸ťłëľĺż´Ŕť °ćżě
        if (t->left_child == NULL && t->right_siblings == NULL)
        {
            if (parent) // şÎ¸đ łëľĺ°Ą NULLŔĚ žĆ´Ň ś§, Áď Á¸ŔçÇŇ ś§
            {
                if (parent->left_child == t)
                    parent->left_child = NULL;
                else
                    parent->right_siblings = NULL;
            }
            else // şÎ¸đ łëľĺ°Ą NULL ŔĚśó¸é, ťčÁŚÇĎˇÁ´Â łëľĺ°Ą ˇçĆŽ łëľĺ´Ů.
                my_tree->root = NULL;
        }
        // ľÎ šřÂ°: ÇĎłŞŔÇ ź­şęĆŽ¸Ž¸¸ °ĄÁö´Â °ćżě
        else if ((t->left_child == NULL) || (t->right_siblings == NULL))
        {
            child = (t->left_child != NULL) ? t->left_child : t->right_siblings;
            if (parent)
            {
                if (parent->left_child == t)
                    parent->left_child = child;
                else
                    parent->right_siblings = child;
            }
            else // şÎ¸đ łëľĺ°Ą NULLŔĚśó¸é ťčÁŚľÇ´Â łëľĺ°Ą ˇçĆŽłëľĺ´Ů.
                my_tree->root = child;
        }
        // źź šřÂ°: ľÎ°łŔÇ ź­şęĆŽ¸Ž¸Ś ¸đľÎ °ĄÁö´Â °ćżě
        else
        {
            // żŔ¸ĽÂĘ ź­şęĆŽ¸ŽżĄź­ °ĄŔĺ ŔŰŔş °ŞŔť ĂŁ´Â´Ů.
            suc_p = t;
            suc = t->right_siblings;
            while (suc->left_child != NULL)
            {
                suc_p = suc;
                suc = suc->left_child;
            }
            // ČÄźÓŔÚŔÇ şÎ¸đżÍ ŔÚ˝ÄŔť żŹ°á
            if (suc_p->left_child == suc)
                suc_p->left_child = suc->right_siblings;
            // żŢÂĘ łĄąîÁö łťˇÁżÔÁö¸¸ ą× łĄżĄ żŔ¸ĽÂĘ ź­şęĆŽ¸Ž°Ą ŔÖŔť źöľľ ŔÖ´ÂľĽ,
            // ŔĚ °ćżě¸Ś ´ëşńÇŘ suc->right °ŞŔť ´ëŔÔÇĎ´Â °ÍŔĚ´Ů.

            else
                suc_p->right_siblings = suc->right_siblings;

            t->data = suc->data;
            t = suc;
        }
        free(t);
        my_tree->count--;
    }

}

void get_ancestors(Tree* my_tree, char data) {//ok
    char anc[10] = { 0, };
    int i = 0;
    Node* cur = search(my_tree, my_tree->root, get_parent(my_tree, data));
    while (cur != my_tree->root) {
        anc[i] = cur->data;
        cur = search(my_tree, my_tree->root, get_parent(my_tree, cur->data));
        i++;
    }
    anc[i] = cur->data;
    for (int j = 0; j < strlen(anc); j++) {
        printf("%c ", anc[j]);
    }
    printf("\n");

}

void get_descendants(Tree* my_tree, char data) {//ok
    char anc[10] = { 0, };
    int i = 0;
    Node* cur = search(my_tree, my_tree->root, data);
    Node* Parent = cur->left_child;
    while (Parent->left_child != NULL) {
        anc[i] = Parent->data;
        Parent = Parent->left_child;
        i++;
    }
    anc[i] = Parent->data;
    for (int j = 0; j < strlen(anc); j++) {
        printf("%c ", anc[j]);
    }
    printf("\n");
}

int degree_of_node(Tree* my_tree, Node* node, char data) {//ok
    if (!node) {
        return NULL;
    }
    if (!(my_tree->binary)) {//ŔĎšÝĆŽ¸Ž
        char c_list[10] = { 0, };
        Node* Parent = search(my_tree, my_tree->root, data);
        Node* child = Parent->left_child;
        int i = 0;
        while (child->right_siblings != NULL) {
            c_list[i] = child->data;
            child = child->right_siblings;
            i++;
        }
        c_list[i] = child->data;
        int dgr = strlen(c_list);
        return dgr;
    }
    else {//ŔĚÁřĆŽ¸Ž
        Node* parent = search(my_tree, my_tree->root, data);
        if (parent->left_child) {
            if (parent->right_siblings) return 2;
            return 1;
        }
        return 0;
    }
}

int degree_of_tree(Tree* my_tree, Node* node) {
    if (node == NULL)
        return 0;
    else {
        int l_degree = degree_of_tree(my_tree, node->left_child);
        int r_degree = degree_of_tree(my_tree, node->right_siblings);
        if (l_degree > r_degree) return l_degree;
        else return r_degree + 1;
    }
}

int count_node(Tree* my_tree) {//ok
    int counting = my_tree->count;
    return counting;
}

void join_trees(char data, Tree* my_tree, Tree* my_tree2) {
    Node* new_root = CreateNode(data);
    my_tree->root->right_siblings = my_tree2->root;
    new_root->left_child = my_tree->root;
    my_tree->root = new_root;
    clear(my_tree2, my_tree2->root);
    printf("\nmy_tree1°ú my_tree2¸Ś ÇŐĂĆ˝Ŕ´Ď´Ů.\n");
}

void give_level(Tree* my_tree, Node* node) {//ok
    if (!node) {
        return;
    }
    give_level(my_tree, node->left_child);
    if (node != my_tree->root) {
        if (get_parent(my_tree, node->data) == my_tree->root->data) {
            node->level = 1;
        }
        else {
            Node* parent_node;
            parent_node = search(my_tree, my_tree->root, get_parent(my_tree, node->data));
            node->level = parent_node->level + 1;
        }
    }
    give_level(my_tree, node->right_siblings);
}


void clear(Tree* my_tree, Node* node) {//ok
    
    __init__(my_tree);
}