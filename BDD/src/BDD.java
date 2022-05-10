
public class BDD {

	int numberOfVariables;
	int numberOfNodes;
	String variableOrder;
	String expression;
	Node root;
	public BDD() {
		// TODO Auto-generated constructor stub
	}
	
	public BDD(String bfunction, String variableOrder) {
		this.numberOfVariables = variableOrder.length();
		this.variableOrder = variableOrder;
		this.expression = bfunction;
		root = BDDController.createBDD(bfunction, variableOrder);
		this.numberOfNodes = BDDController.getNumberOfNodes();
	}

}
