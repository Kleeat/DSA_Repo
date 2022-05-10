import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Tester {

	public Tester() {
		// TODO Auto-generated constructor stub
	}

	public static void test(int lenght, int numberOfTimes) {
		long averageCreateTime = 0;
		long averageTraverseTime = 0;
		float averageReduction = 0;
		BDDController controller = new BDDController();
		long allNodes = 0;
		for (int i = 0; i < lenght; i++) {
			allNodes += (long)Math.pow(2, i);
		}
		for (int i = 0; i < numberOfTimes; i++) {
			String bfunction = generateBFunction(lenght);
			String variableOrder = generateOrder(lenght);
			System.out.println(bfunction);
			// Creating the BDD
			long start = System.nanoTime();
			BDD bdd = BDDController.BDDcreate(bfunction, variableOrder);
			long end = System.nanoTime();
			averageCreateTime += (end - start);
			System.out.println("BDD created in: " + (end - start) + " nanoseconds");
			float reduction = ((float)(allNodes - bdd.numberOfNodes) / allNodes) * 100; 
			System.out.println("Reduction percentage: " + reduction + "%");
			averageReduction += reduction;
			// Using the BDD for all values
			averageTraverseTime += getValues(bdd);
			System.out.println();
 		}
		averageCreateTime /= numberOfTimes;
		System.out.println("Average time to create BDD in nanoseconds is: " + averageCreateTime);
		averageReduction /= numberOfTimes;
		System.out.println("Average reduction precentage: " + averageReduction + "%");
		averageTraverseTime /= numberOfTimes;
		System.out.println("Average time to evaluate expression in nanoseconds is : " + averageTraverseTime);
	}
	
	
	public static long getValues(BDD bdd) {
		long time = 0;
		for (int i = 0; i < Math.pow(2, bdd.numberOfVariables); i++) {
			String value = Integer.toBinaryString(i);
			while(value.length() != bdd.numberOfVariables) {
				value = "0" + value;
			}
			// Looking trough the tree
			long start = System.nanoTime();
			int result = BDDController.BDDuse(bdd, value);
			int expectedResult = Tester.booleanSolver(bdd, value);
			long end = System.nanoTime();
			time += (end - start);
			
			System.out.print(value + " -> ");
			System.out.print(result + " expected -> ");
			System.out.println(expectedResult);
			if (result != expectedResult) {
				System.out.println("-----ERROR RESULT AND EXPECTED RESULT DO NOT MATCH!-----");
			}
		}
		System.out.println("Time to traverse tree in nanoseconds: " + time);
		return time;
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
		// Lenght of the boolean expression, how many ()
		final int length = 6;
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
