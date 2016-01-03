import java.awt.*;
import java.util.*;

public class Christofides {
    public static void main(String[] args) {
        new Christofides().run();
    }

    private GraphFrame graphFrame;

    private void run() {
        RandomGraph randomGraph = new RandomGraph();
        ArrayList<Vertex> vertices = randomGraph.randomVertices(500, 100.0);
        Random random = new Random();
        int start = random.nextInt(vertices.size());
        int finish = start;
        do {
            finish = random.nextInt(vertices.size());
        } while (finish == start);

        Graph G = new Graph(vertices, start, finish);
        G.printGraph();

        graphFrame = new GraphFrame(G, 100);
        graphFrame.setVisible(true);

        Graph MST = findMST(G);
        int E = MST.getM();

        graphFrame.sleep();

        Graph PM = findPM(findWrongVertices(MST));
        MST.addEdges(PM.getEdges());

        graphFrame.sleep();

        ArrayList<Vertex> HP = findHP(findEP(MST), MST);

        System.out.println("Hamiltonian path:");
        for (Vertex v : HP) {
            System.out.print((v.ind + 1) + " ");
        }
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
                graphFrame.getGraphPanel().addEdge(e, Color.black, false);
            }
        }

        return mst;
    }

    private ArrayList<Vertex> findWrongVertices(Graph G) {
        HashMap<Vertex, Integer> degree = new HashMap<>();
        ArrayList<Edge> edges = G.getEdges();

        for (Edge e : edges) {
            degree.put(e.u, (degree.containsKey(e.u) ? degree.get(e.u) : 0) + 1);
            degree.put(e.v, (degree.containsKey(e.v) ? degree.get(e.v) : 0) + 1);
        }

        ArrayList<Vertex> vertices = G.getVertices();
        ArrayList<Vertex> wrong = new ArrayList<>();

        for (Vertex v : vertices) {
            if (!degree.containsKey(v)) {
                continue;
            }
            int deg = degree.get(v);
            if (G.isStart(v) || G.isFinish(v)) {
                if (deg % 2 == 0) {
                    wrong.add(v);
                }
            } else {
                if (deg % 2 == 1) {
                    wrong.add(v);
                }
            }
        }

        return wrong;
    }

    private Graph findPM(ArrayList<Vertex> V) {
        Random random = new Random();

        int k = (int)Math.ceil(Math.sqrt((double)V.size())) + V.size() / 10;
        double eps = (1 + 1.0 / k) * (1 + 1.0 / k);

        ArrayList<Vertex> W = new ArrayList<>(V);
        Graph PM = new Graph(V);

        for (int i = 0; i < k && !W.isEmpty(); ++i) {
            Vertex v = W.get(random.nextInt(W.size()));
            Vertex u = Vertex.getNearest(v, W);
            Vertex vv = Vertex.getNearest(v, V);
            Vertex uu = Vertex.getNearest(u, V);
            if (Vertex.admissible(v, u, vv, uu, eps)) {
                Edge e = new Edge(u, v);
                PM.addEdge(e);
                graphFrame.getGraphPanel().addEdge(e, Color.blue, false);
                W.remove(u);
                W.remove(v);
            }
        }

        while (!W.isEmpty()) {
            Vertex v = W.get(random.nextInt(W.size()));
            Vertex u = Vertex.getNearest(v, W);
            Edge e = new Edge(u, v);
            PM.addEdge(e);
            graphFrame.getGraphPanel().addEdge(e, Color.blue, false);
            W.remove(u);
            W.remove(v);
        }

        return PM;
    }

    private ArrayList<Vertex> findEP(Graph G) {
        int n = G.getN();
        int[][] adj = new int[n][n];

        for (Edge e : G.getEdges()) {
            ++adj[e.u.ind][e.v.ind];
            ++adj[e.v.ind][e.u.ind];
        }

        ArrayList<Vertex> eulerPath = new ArrayList<>();
        Stack<Integer> st = new Stack<>();
        st.push(G.getStart());

        while (!st.isEmpty()) {
            int v = st.peek();
            int i;
            for (i = 0; i < n; ++i) {
                if (adj[v][i] != 0) {
                    break;
                }
            }
            if (i == n) {
                eulerPath.add(G.getVertexByInd(v));
                st.pop();
            } else {
                --adj[v][i];
                --adj[i][v];
                st.push(i);
            }
        }

        graphFrame.getGraphPanel().drawPath(eulerPath, Color.red);

        return eulerPath;
    }

    private ArrayList<Vertex> findHP(ArrayList<Vertex> eulerPath, Graph G) {
        int n = eulerPath.size();
        Collections.reverse(eulerPath);
        boolean[] used = new boolean[n];
        ArrayList<Vertex> hamiltonianPath = new ArrayList<>();

        for (Vertex vert : eulerPath) {
            int v = vert.ind;
            if (!used[v] && v != G.getFinish()) {
                hamiltonianPath.add(G.getVertexByInd(v));
            }
            used[v] = true;
        }

        hamiltonianPath.add(G.getVertexByInd(G.getFinish()));

        graphFrame.getGraphPanel().drawPath(hamiltonianPath, Color.black);
        graphFrame.getGraphPanel().finalize(hamiltonianPath);

        return hamiltonianPath;
    }
}
