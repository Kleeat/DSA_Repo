
public class Main {

	public static BDD bdd;
	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		String bfunction = Tester.generateBFunction(3);
		System.out.println(bfunction);
		bdd = BDDcreate(bfunction, "acb");
		Tester.generate(3);
		for (int i = 0; i < 10; i++) {
			System.out.println(Tester.generateOrder(4)); 
		}
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
