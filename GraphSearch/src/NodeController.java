import java.util.ArrayList;
import java.util.Random;

public class NodeController {

	private static ArrayList<Node> nodeList = new ArrayList<>();
	
	public NodeController() {
		// TODO Auto-generated constructor stub
	}
	public static ArrayList<Node> getNodeList() {
		return nodeList;
	}
	
	public static void printNodes() {
		for (Node node : nodeList) {
			System.out.print("I am node" + node.getNodeIndex() + " my neighbours are: ");
			for (Node node2 : node.getNeighbourList()) {
				System.out.print("node" + node2.getNodeIndex() + "; ");
			}
			System.out.print("\n");
		}
	}
	
	public static void doDFS() {
		Random random = new Random();
		ArrayList<Node> printedNodes = new ArrayList<>();
		System.out.print("DFS:");
		dfs(getNodeList().get(random.nextInt(getNodeList().size())), printedNodes);
	}
	
	private static void dfs(Node rootNode, ArrayList<Node> printedNodes) {
		System.out.print(" node" + rootNode.getNodeIndex() + ";");
		printedNodes.add(rootNode);
		for (Node node : rootNode.getNeighbourList()) {
			if (!printedNodes.contains(node)) {
				dfs(node, printedNodes);
			}
		}
	}
	
	public static void doBFS() {
		Random random = new Random();
		ArrayList<Node> printedNodes = new ArrayList<>();
		System.out.print("BFS:");
		Node rootNode = getNodeList().get(random.nextInt(getNodeList().size()));
		System.out.print(" node" + rootNode.getNodeIndex() + ";");
		bfs(rootNode, printedNodes);
	}
	
	private static void bfs(Node rootNode, ArrayList<Node> printedNodes) {
		for (Node node : rootNode.getNeighbourList()) {
			System.out.print(" node" + node.getNodeIndex() + ";");
			printedNodes.add(node);
		}
		for (Node node : rootNode.getNeighbourList()) {
			if (!printedNodes.contains(node)) {
				dfs(node, printedNodes);
			}
		}
	}
}
