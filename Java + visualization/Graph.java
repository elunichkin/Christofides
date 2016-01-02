import java.util.ArrayList;

public class Graph {
    private int n, m;
    private ArrayList<Vertex> v;
    private ArrayList<Edge> e;

    public Graph(ArrayList<Vertex> vs) {
        this.n = vs.size();
        v = vs;
    }

    public Graph(Graph other) {
        this(other.getVertices());
    }

    public void induce() {
        m = n * (n-1) / 2;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                e.add(new Edge(v.get(i), v.get(j)));
            }
        }
    }

    public void addVertex(Vertex vertex) {
        ++n;
        v.add(vertex);
    }

    public void addEdge(Edge edge) {
        ++m;
        e.add(edge);
    }

    public int getN() {
        return n;
    }

    public int getM() {
        return m;
    }

    public ArrayList<Vertex> getVertices() {
        return v;
    }

    public ArrayList<Edge> getEdges() {
        return e;
    }
}
