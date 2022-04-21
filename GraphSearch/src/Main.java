
public class Main {

	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		for (int i = 0; i < 10; i++) {
			Node node = new Node();
			node.setNodeIndex(i);
		}
		NodeController.printNodes();
		NodeController.doDFS();
		NodeController.doBFS();
	}

}
