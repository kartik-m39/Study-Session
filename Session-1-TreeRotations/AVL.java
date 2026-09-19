class AVL {
  public class Node {
    private int value;
    private Node left;
    private Node right;
    private int height;

    public Node(int value) {
      this.value = value;
    }

    public int getValue() {
      return value;
    }
  }

  private Node root;

  public AVL() {

  }

  public void insert(int value) {
    root = insert(value, root);
  }






  private Node insert(int value, Node node) {
    if (node == null) {
      node = new Node(value);
      return node;
    }

    if (value < node.value) {
      node.left = insert(value, node.left);
    }

    if (value > node.value) {
      node.right = insert(value, node.right);
    }

    node.height = Math.max(height(node.left), height(node.right)) + 1;

    // return rotate(node);
    return node;
  }


  private Node rotate(Node node){

    // Tree is imbalanced

    // LEFT heavy
    if(height(node.left) - height(node.right) > 1){

      // LL case
      if(height(node.left.left) - height(node.left.right) > 0){
        return rightRotate(node);
      }

      // LR case
      if(height(node.left.left) - height(node.left.right) < 0){
        
        // we do left rotate on node.left ie the child
        node.left = leftRotate(node.left);
        return rightRotate(node);
      }
    }

    // RIGHT heavy
    if(height(node.left) - height(node.right) < -1){

      // RR case
      if(height(node.right.left) - height(node.right.right) < 0){
        return leftRotate(node);
      }

      // RL case
      if(height(node.right.left) - height(node.right.right) > 0){
        
        // we do first right rotate on node.left ie the child
        node.right = rightRotate(node.right);
        return leftRotate(node);   //Then left rotate on the node
      }
    }

    return node;
  }

  public Node leftRotate(Node c){
    Node p = c.right;
    Node t = p.left;

    p.left = c;
    c.right = t;

    c.height = Math.max(height(c.left), height(c.right)) + 1;
    p.height = Math.max(height(p.left), height(p.right)) + 1;

    // return the new node
    return p;
  }

  public Node rightRotate(Node p){
    Node c = p.left;
    Node t = c.right;

    c.right = p;
    p.left = t;

    p.height = Math.max(height(p.left), height(p.right)) + 1;
    c.height = Math.max(height(c.left), height(c.right)) + 1;

    // return the new node
    return c;
  }







  public void display() {
    display(root, 0);
}

  private void display(Node node, int level) {
      if (node == null) {
          return;
      }

      display(node.right, level + 1);

      for (int i = 0; i < level; i++) {
          System.out.print("    ");
      }

      System.out.println(node.value);

      display(node.left, level + 1);
  }

  public boolean isEmpty() {
    return root == null;
  }

  public int height() {
    if (root == null) {
      return -1;
    }
    return root.height;
  }

  public int height(Node node) {
    if (node == null) {
      return -1;
    }
    return node.height;
  }

  public boolean balanced() {
    return balanced(root);
  }

  private boolean balanced(Node node) {
    if (node == null) {
      return true;
    }
    return Math.abs(height(node.left) - height(node.right)) <= 1 && balanced(node.left) && balanced(node.right);
  }

  public static void main(String[] args) {
      AVL tree = new AVL();

      for(int i = 0; i < 1000; i++){
        tree.insert(i);
      }
      System.out.println(tree.balanced());
      System.out.println(tree.height());

      // tree.display();
      
  }
}
