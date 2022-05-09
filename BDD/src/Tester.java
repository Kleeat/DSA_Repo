import java.util.Random;

public class Tester {

	public Tester() {
		// TODO Auto-generated constructor stub
	}

	public static void generate(int length) {
		for (int i = 0; i < Math.pow(2, length); i++) {
			String value = Integer.toBinaryString(i);
			while(value.length() != length) {
				value = "0" + value;
			}
			System.out.print(value + " -> ");
			Main.BDDuse(Main.bdd, value);
		}
	}
	
	public static String generateBFunction(int numberOfVariables) {
		String bfunction = "";
		char variable;
		final int length = 5;
		int removedVariables;
		Random random = new Random();
		for (int i = 0; i < length; i++) {
			removedVariables = 0;
			for (int j = 0; j < numberOfVariables ; j++) {
				if (random.nextBoolean()) {
					if (removedVariables < (double)numberOfVariables / 2) {
						removedVariables++;
						continue;
					}
				}
				if (random.nextBoolean()) {
					bfunction += "!";
				}
				variable = (char)(j + 97);
				bfunction += variable;
			}
			if (i != length - 1) {
				bfunction += "+";
			}
		}
		return bfunction;
	}
}
