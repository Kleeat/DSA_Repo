
public class Main {

	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		//BDDcreate("a!b!c+!a!bc+ab!c+!ab!c", "abc");
		BDDController controller = new BDDController();
		System.out.println(controller.extractHigh("a!b!c+!a!bc+ab!c+!ab!c+ab!c", 'c'));
		
	}

	public static void BDDcreate(String bfunction, String variableOrder) {
		BDD newBDD = new BDD(bfunction, variableOrder);
	}
}
