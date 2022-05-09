
public class Main {

	public static BDD bdd;
	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		System.out.println(Tester.generateBFunction(5));
		//bdd = BDDcreate("a!b!c+!a!bc+ab!c+!ab!c+ab!c+a!b+cb", "acb");
		//Tester.generate(3);
		//BDDController controller = new BDDController();
		//System.out.println(controller.extractHigh("a", 'c'));
		//System.out.println(controller.extractLow("!b!c+b!c+!b+cb", 'c'));
		
	}

	public static BDD BDDcreate(String bfunction, String variableOrder) {
		return new BDD(bfunction, variableOrder);
	}
	public static void BDDuse(BDD bdd, String input) {
		System.out.println(BDDController.evaluate(bdd, input));
	}
}
