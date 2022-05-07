
public class BDD {

	int numberOfVariables;
	int numberOfNodes;
	Node root = new Node();
	public BDD() {
		// TODO Auto-generated constructor stub
	}
	
	public BDD(String bfunction, String variableOrder) {
		this.numberOfVariables = variableOrder.length();
		this.numberOfNodes = (int) Math.pow(2, numberOfVariables);
		BDDController controller = new BDDController(root);
		root = controller.createBDD(null, bfunction, variableOrder);
	}

}
