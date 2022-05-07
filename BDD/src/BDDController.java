import java.util.ArrayList;
import java.util.List;

public class BDDController {

	public static Node zero = new Node("0", '0');
	public static Node one = new Node("1", '1');
	private ArrayList<Node> existingNodes = new ArrayList<Node>();
	
	public BDDController() {
		// TODO Auto-generated constructor stub
	}
	
	// Creating the reduced BDD
	public Node createBDD(String bfunction, String variableOrder) {
		for (Node node : existingNodes) {
			if (node.expression.equals(bfunction)) {
				return node;
			}
		}
		// Creating the node that will be returned
		Node node = new Node(bfunction, variableOrder.charAt(0));
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
			existingNodes.add(node);
			return node;
		}
		// Preparing for adding the children
		String highFunction = extractHigh(bfunction, variableOrder.charAt(0));
		String lowFunction = extractLow(bfunction, variableOrder.charAt(0));
		String newOrder = popOrder(variableOrder);
		// Not adding useless nodes
		if (highFunction.equals(lowFunction)) {
			return createBDD(highFunction, newOrder);
		}
		// Else branch out from this node
		node.highChild = createBDD(highFunction, newOrder);
		node.lowChild = createBDD(lowFunction, newOrder);
		existingNodes.add(node);
		return node;
	}
	
	// Parsing expression to extract the expression for the high child 
	public String extractHigh(String bfunction, char variable) {
		int i = 0;
		List<String> expressions = new ArrayList<String>();
		String temp = "";
		while(i <= bfunction.length()) {
			if (i == bfunction.length() || bfunction.charAt(i) == '+') {
				if ((temp.indexOf("!" + variable) < 0 && !expressions.contains(temp)) || temp.indexOf(variable) < 0 ) { 
					expressions.add(temp);
				}
				temp = "";
				i++;
				continue;
			}
			temp += bfunction.charAt(i);
			i++;
		}
		temp = "";
		for (String string : expressions) {
			i = 0;
			if (!temp.isEmpty()) {
				temp += "+";
			}
			while (i < string.length()) {
				if (i == string.indexOf(variable)) {
					i++;
					continue;
				}
				temp += string.charAt(i);
				i++;
			}
		}
		return temp;
	}
	
	
	
	// Parsing expression to extract the expression for the low child 
	public String extractLow(String bfunction, char variable) {
		int i = 0;
		List<String> expressions = new ArrayList<String>();
		String temp = "";
		while(i <= bfunction.length()) {
			if (i == bfunction.length() || bfunction.charAt(i) == '+') {
				if ((temp.indexOf("!" + variable) >= 0 && !expressions.contains(temp)) || temp.indexOf(variable) < 0 ) { 
					expressions.add(temp);
				}
				temp = "";
				i++;
				continue;
			}
			temp += bfunction.charAt(i);
			i++;
		}
		temp = "";
		for (String string : expressions) {
			i = 0;
			if (!temp.isEmpty()) {
				temp += "+";
			}
			while (i < string.length()) {
				if (i == string.indexOf(variable)-1) {
					i+=2;
					continue;
				}
				temp += string.charAt(i);
				i++;
			}
		}
		return temp;
	}
	
	// Shifting the string to the left
	private String popOrder(String variableOrder) {
		String newOrder = "";
		int i = 0;
		while(variableOrder.length() > i+1) {
			newOrder = newOrder + variableOrder.charAt(i+1);
			i++;
		}
		return newOrder;
	}

	public int getNumberOfNodes() {
		return existingNodes.size();
	}
}
