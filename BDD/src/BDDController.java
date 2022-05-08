import java.util.ArrayList;
import java.util.List;

public class BDDController {

	public static Node zero = new Node("0", '0');
	public static Node one = new Node("1", '1');
	private ArrayList<Node> existingNodes = new ArrayList<Node>();
	
	public BDDController() {
		// TODO Auto-generated constructor stub
	}
	
	// Use the bdd
	public static int evaluate(BDD bdd, String input) {
		if (bdd.variableOrder.length() != input.length()) {
			return -1;
		}
		Node root = bdd.root;
		char value;
		try {
			while (root != zero && root != one) {
				value = input.charAt(root.variable - 97);
				if (value == '1') {
					root = root.highChild;
				} else {
					root = root.lowChild;
				}
			}
			if(root == zero) {
				return 0;
			}
			else 
				return 1; 
			
		} catch (Exception e) {
			return -1;
		}
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
		// Preparing for adding the children
		String highFunction = extractHigh(bfunction, variableOrder.charAt(0));
		String lowFunction = extractLow(bfunction, variableOrder.charAt(0));
		String newOrder = popOrder(variableOrder);
		// Not adding useless nodes
		if (highFunction.equals(lowFunction)) {
			if (highFunction.equals("1")) {
				return one;
			} else if (highFunction.isEmpty()) {
				return zero;
			}
			return createBDD(highFunction, newOrder);
		}
		// Checking for leaves
		if (highFunction.isEmpty()) {
			node.highChild = zero;
		}
		if (highFunction.equals("1")) {
			node.highChild = one;
		}
		if (lowFunction.isEmpty()) {
			node.lowChild = zero;
		}
		if (lowFunction.equals("1")) {
			node.lowChild = one;
		}
		// Else branch out from this node
		if (node.highChild == null) {
			node.highChild = createBDD(highFunction, newOrder);
		}
		if (node.lowChild == null) {
			node.lowChild = createBDD(lowFunction, newOrder);
		}
		existingNodes.add(node);
		return node;
	}
	
	// Parsing expression to extract the expression for the high child 
	public String extractHigh(String bfunction, char variable) {
		int i = 0;
		int j = 0;
		List<String> expressions = new ArrayList<String>();
		String temp = "";
		String temp2;
		while(i <= bfunction.length()) {
			if (i == bfunction.length() || bfunction.charAt(i) == '+') {
				if (temp.indexOf("!" + variable) < 0) { 
					temp2 = "";
					j = 0;
					if (temp.equals(Character.toString(variable))) {
						return "1";
					}
					// Remove variable from expression
					while (j < temp.length()) {
						if (j == temp.indexOf(variable)) {
							j++;
							continue;
						}
						temp2 += temp.charAt(j);
						j++;
					}
					// Add expressions
					if (!expressions.contains(temp2)) {
						expressions.add(temp2);
					}
				}
				if (!expressions.contains(temp) && temp.indexOf(variable) < 0) {
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
			if (!temp.isEmpty()) {
				temp += "+";
			}
			temp += string;
		}
		return temp;
	}
	
	
	
	// Parsing expression to extract the expression for the low child 
	public String extractLow(String bfunction, char variable) {
		int i = 0;
		int j = 0;
		List<String> expressions = new ArrayList<String>();
		String temp = "";
		String temp2;
		while(i <= bfunction.length()) {
			if (i == bfunction.length() || bfunction.charAt(i) == '+') {
				if (temp.indexOf("!" + variable) >= 0 && !expressions.contains(temp)) { 
					temp2 = "";
					j = 0;
					if (temp.equals("!" + variable)) {
						return "1";
					}
					// Remove variable from expression
					while (j < temp.length()) {
						if (j == temp.indexOf(variable)-1) {
							j+=2;
							continue;
						}
						temp2 += temp.charAt(j);
						j++;
					}
					// Add expressions
					if (!expressions.contains(temp2)) {
						expressions.add(temp2);
					}
				}
				if (!expressions.contains(temp) && temp.indexOf(variable) < 0 ) {
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
			if (!temp.isEmpty()) {
				temp += "+";
			}
				temp += string;
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
