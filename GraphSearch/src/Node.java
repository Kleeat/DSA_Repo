import java.util.ArrayList;
import java.util.Random;

public class Node {

	private ArrayList<Node> neighbourList = new ArrayList<Node>();
	private int nodeIndex;
	
	// Constructor for node that automaticallz adds neighbours
	public Node() {
		Node node;
		if (NodeController.getNodeList().isEmpty()) {
			NodeController.getNodeList().add(this);
			return;
		}
		
		// Selecting a random neighbour
		Random random = new Random();
		node = NodeController.getNodeList().get(random.nextInt(NodeController.getNodeList().size()));
		neighbourList.add(node);
		node.neighbourList.add(this);
		
		// Adding extra neighbours
		for (Node node2 : NodeController.getNodeList()) {
			if(random.nextDouble() > 0.9 && !neighbourList.contains(node2)) {
				neighbourList.add(node2);
				node2.neighbourList.add(this);
			}
		}
		// Finally adding node to all nodes list
		NodeController.getNodeList().add(this);
		return;
	}
	
	// Getter for neighbour list
	public ArrayList<Node> getNeighbourList(){
		return neighbourList;
	}

	public int getNodeIndex() {
		return nodeIndex;
	}

	public void setNodeIndex(int nodeIndex) {
		this.nodeIndex = nodeIndex;
	}

}
