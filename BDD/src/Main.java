
public class Main {

	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		BDDcreate("a!b!c+!a!bc+ab!c+!ab!c", "abc");
	}

	public static void BDDcreate(String bfunction, String variableOrder) {
		BDD newBDD = new BDD(bfunction, variableOrder);
	}
}
