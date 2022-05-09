
public class BDD {

	int numberOfVariables;
	int numberOfNodes;
	String variableOrder;
	String expression;
	Node root = new Node();
	public BDD() {
		// TODO Auto-generated constructor stub
	}
	
	public BDD(String bfunction, String variableOrder) {
		this.numberOfVariables = variableOrder.length();
		this.variableOrder = variableOrder;
		this.expression = bfunction;
		BDDController controller = new BDDController();
		root = controller.createBDD(bfunction, variableOrder);
		this.numberOfNodes = controller.getNumberOfNodes();
	}

}
