import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Tester {

	public Tester() {
		// TODO Auto-generated constructor stub
	}

	public static void test(int lenght, int numberOfTimes) {
		for (int i = 0; i < numberOfTimes; i++) {
			String bfunction = generateBFunction(lenght);
			String variableOrder = generateOrder(lenght);
			System.out.println(bfunction);
			long start = System.nanoTime();
			BDD bdd = BDDController.BDDcreate(bfunction, variableOrder);
			long end = System.nanoTime();
			System.out.println("BDD created in: " + (end - start) + " nanoseconds");
			getValues(bdd);
			System.out.println();
 		}
	}
	public static void getValues(BDD bdd) {
		for (int i = 0; i < Math.pow(2, bdd.numberOfVariables); i++) {
			String value = Integer.toBinaryString(i);
			while(value.length() != bdd.numberOfVariables) {
				value = "0" + value;
			}
			System.out.print(value + " -> ");
			System.out.print(BDDController.BDDuse(bdd, value) + " expected -> ");
			System.out.println(Tester.booleanSolver(bdd, value));
			
			
		}
	}
	
	public static String generateOrder(int numberOfVariables) {
		String variableOrder = "";
		List<Character> variableList = new ArrayList<Character>();
		for(int i = 0; i < numberOfVariables; i++ ) {
			variableList.add((char)(i+97));
		}
		Collections.shuffle(variableList);
		for(int i = 0; i < numberOfVariables; i++ ) {
			variableOrder += Character.toString(variableList.get(i));
		}
		return variableOrder;
	}
	
	public static int booleanSolver(BDD bdd, String input) {
		int value = 1;
		int index;
		int i = 0;
		String bfunction = bdd.expression;
		if (input.length() != bdd.numberOfVariables) {
			return -1;
		}
		while (i < bfunction.length()) {
			if (bfunction.charAt(i) == '!') {
				i++;
				index = (int)bfunction.charAt(i) - 97;
				value *= 1 - ((int)input.charAt(index) - 48);
				i++;
				continue;
			}
			if (bfunction.charAt(i) == '+') {
				if (value > 0) {
					return 1;
				}
				i++;
				value = 1;
				continue;
			}
			index = (int)bfunction.charAt(i) - 97;
			value *= (int)input.charAt(index) - 48;
			i++;
		}
		if (value > 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	
	public static String generateBFunction(int numberOfVariables) {
		String bfunction = "";
		char variable;
		final int length = 3;
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
