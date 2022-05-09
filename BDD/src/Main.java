
public class Main {

	public static BDD bdd;
	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		//String bfunction = Tester.generateBFunction(3);
		//System.out.println(bfunction);
		//bdd = BDDController.BDDcreate(bfunction, "acb");
		Tester.test(3, 10);
		/*for (int i = 0; i < 10; i++) {
			System.out.println(Tester.generateOrder(4)); 
		}
		*/
		//BDDController controller = new BDDController();
		//System.out.println(controller.extractHigh("a", 'c'));
		//System.out.println(controller.extractLow("!b!c+b!c+!b+cb", 'c'));
		
	}
}
