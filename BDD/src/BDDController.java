
public class BDDController {

	public static Node zero = new Node("0", '0');
	public static Node one = new Node("1", '1');
	private Node root;
	
	public BDDController() {
		// TODO Auto-generated constructor stub
	}
	
	public BDDController(Node root) {
		this.root = root;
	}
	
	public Node createBDD(Node parent, String bfunction, String variableOrder) {
		// Creating the node that will be returned
		Node node = new Node(bfunction, variableOrder.charAt(0), parent);
		// Preparing for adding the childs
		// Checking for leaves
		if (variableOrder.length() == 1) {
			if (bfunction.charAt(0) == '!') {
				node.highChild = zero;
				node.lowChild = one;
			}
			else {
				node.highChild = one;
				node.lowChild = zero;
			}
			return node;
		}
		// Else branch out from this node
		String highFunction = extractHigh(bfunction, variableOrder.charAt(0));
		String lowFunction = extractLow(bfunction, variableOrder.charAt(0));
		String newOrder = popOrder(variableOrder);
		node.highChild = createBDD(node, highFunction, newOrder);
		node.lowChild = createBDD(node, lowFunction, newOrder);
		
		return node;
	}
	
	// Parsing expression to extract the expression for the high child
	public static String extractHigh(String bfunction, char variable) {
		String highFunction = "";
		int i = 0;
		while (bfunction.length() > i) {
			if (bfunction.charAt(i) != variable) {
				while (bfunction.length() > i) {
					if (bfunction.charAt(i) == '+') {
						i++;
						break;
					}
					else
						i++;
				}
			}
			else {
				if (!highFunction.isEmpty()) {
					highFunction = highFunction + '+';
				}
				i++;
				while(bfunction.length() > i && bfunction.charAt(i) != '+') {
					highFunction = highFunction + bfunction.charAt(i);
					i++;
				}
				i++;
			}
		}
		return highFunction;
	}
	
	// Parsing expression to extract the expression for the low child 
	public static String extractLow(String bfunction, char variable) {
		String lowFunction = "";
		int i = 0;
		while (bfunction.length() > i) {
			if (bfunction.charAt(i) != '!' &&  bfunction.charAt(i+1) != variable) {
				while (bfunction.length() > i) {
					if (bfunction.charAt(i) == '+') {
						i++;
						break;
					}
					else
						i++;
				}
			}
			else {
				if (!lowFunction.isEmpty()) {
					lowFunction = lowFunction + '+';
				}
				i += 2;
				while(bfunction.length() > i && bfunction.charAt(i) != '+') {
					lowFunction = lowFunction + bfunction.charAt(i);
					i++;
				}
				i++;
			}
		}
		return lowFunction;
	}
	
	// Shifting the string to the left
	public static String popOrder(String variableOrder) {
		String newOrder = "";
		int i = 0;
		while(variableOrder.length() > i+1) {
			newOrder = newOrder + variableOrder.charAt(i+1);
			i++;
		}
		return newOrder;
	}
}
