import java.util.ArrayList;
import java.util.Collections;

public class Graph {
    private int n, m;
    private int start, finish;
    private ArrayList<Vertex> v;
    private ArrayList<Edge> e;

    public Graph() {
        this.n = 0;
        this.m = 0;
        this.v = new ArrayList<>();
        this.e = new ArrayList<>();
    }

    public Graph(ArrayList<Vertex> vs) {
        this.n = vs.size();
        this.m = 0;
        this.v = vs;
        this.e = new ArrayList<>();
    }

    public Graph(Graph other) {
        this(other.getVertices());
        this.start = other.getStart();
        this.finish = other.getFinish();
    }

    public Graph(ArrayList<Vertex> vs, int s, int f) {
        this(vs);
        this.start = s;
        this.finish = f;
        this.induce();
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

    public int getStart() {
        return start;
    }

    public int getFinish() {
        return finish;
    }

    public Vertex getVertexByInd(int ind) {
        for (Vertex vertex : v) {
            if (vertex.ind == ind) {
                return vertex;
            }
        }
        return null;
    }

    public boolean isStart(Vertex v) {
        return v.ind == start;
    }

    public boolean isFinish(Vertex v) {
        return v.ind == finish;
    }

    public void addEdges(ArrayList<Edge> edges) {
        for (Edge edge : edges) {
            addEdge(edge);
        }
    }

    public void printGraph() {
        System.out.println("Vertices:");
        for (Vertex vertex : v) {
            System.out.println((vertex.ind + 1) + " " + vertex.x + " " + vertex.y);
        }
        System.out.println("Start: " + (start + 1) + "\nFinish: " + (finish + 1) + "\n");
    }
}
