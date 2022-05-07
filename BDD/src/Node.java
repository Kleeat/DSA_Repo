
public class Node {

	String expression;
	char variable;
	Node parent = null;
	Node highChild = null;
	Node lowChild = null; 
	
	public Node() {
		// TODO Auto-generated constructor stub
	}
	
	public Node(String expression, char variable) {
		this.expression = expression;
		this.variable = variable;
	}
	
	public Node(String expression, char variable, Node parent) {
		this.expression = expression;
		this.variable = variable;
		this.parent = parent;
	}
	

}
