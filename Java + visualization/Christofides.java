import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Random;

public class Christofides {
    public static void main(String[] args) {
        new Christofides().run();
    }

    private void run() {

    }

    private Graph findMST(Graph G) {
        Graph mst = new Graph(G);
        DSU dsu = new DSU(G.getN());
        ArrayList<Edge> edges = G.getEdges();
        Collections.sort(edges);

        for (Edge e : edges) {
            int u = e.u.ind;
            int v = e.v.ind;
            if (dsu.find(u) != dsu.find(v)) {
                dsu.unite(u, v);
                mst.addEdge(e);
            }
        }

        return mst;
    }

    private Graph findWrongVertices(Graph G) {
        HashMap<Vertex, Integer> degree = new HashMap<>();
        ArrayList<Edge> edges = G.getEdges();

        for (Edge e : edges) {
            degree.put(e.u, (degree.containsKey(e.u) ? degree.get(e.u) : 0) + 1);
            degree.put(e.v, (degree.containsKey(e.v) ? degree.get(e.v) : 0) + 1);
        }

        Graph wrong = new Graph();
        ArrayList<Vertex> vertices = G.getVertices();

        for (Vertex v : vertices) {
            if (!degree.containsKey(v)) {
                continue;
            }
            int deg = degree.get(v);
            if (G.isStart(v) || G.isFinish(v)) {
                if (deg % 2 == 0) {
                    wrong.addVertex(v);
                }
            } else {
                if (deg % 2 == 1) {
                    wrong.addVertex(v);
                }
            }
        }

        wrong.induce();
        return wrong;
    }

    private Graph findPM(Graph G) {
        Random random = new Random();

        int k = (int)Math.ceil(Math.sqrt((double)G.getN()));
        double eps = 1.0 / k;

        ArrayList<Vertex> V = G.getVertices();
        ArrayList<Vertex> W = new ArrayList<>(V);
        Graph PM = new Graph(G);

        for (int i = 0; i < k && !W.isEmpty(); ++i) {
            Vertex v = W.get(random.nextInt(W.size()));
            Vertex u = Vertex.getNearest(v, W);
            Vertex vv = Vertex.getNearest(v, V);
            Vertex uu = Vertex.getNearest(u, V);
            if (Vertex.admissible(v, u, vv, uu, eps)) {
                PM.addEdge(new Edge(u, v));
                W.remove(u);
                W.remove(v);
            }
        }

        while (!W.isEmpty()) {
            Vertex v = W.get(random.nextInt(W.size()));
            Vertex u = Vertex.getNearest(v, W);
            PM.addEdge(new Edge(u, v));
            W.remove(u);
            W.remove(v);
        }

        return PM;
    }
}
