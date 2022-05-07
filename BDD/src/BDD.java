
public class BDD {

	int numberOfVariables;
	int numberOfNodes;
	Node root = new Node();
	public BDD() {
		// TODO Auto-generated constructor stub
	}
	
	public BDD(String bfunction, String variableOrder) {
		this.numberOfVariables = variableOrder.length();
		BDDController controller = new BDDController();
		root = controller.createBDD(bfunction, variableOrder);
		this.numberOfNodes = controller.getNumberOfNodes();
	}

}
