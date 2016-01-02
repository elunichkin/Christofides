import java.util.ArrayList;
import java.util.Collections;

public class Christofides {
    public static void main(String[] args) {
        new Christofides().run();
    }

    private void run() {

    }

    private Graph MST(Graph G) {
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
}
