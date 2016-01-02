import java.util.ArrayList;

public class Vertex {
    public static double eps = 1e-6;

    public static double dist(Vertex a, Vertex b) {
        return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    public static Vertex getNearest(Vertex u, ArrayList<Vertex> vs) {
        if (vs.isEmpty()) {
            return null;
        }
        Vertex nearest = vs.get(0);
        double dist = Double.MAX_VALUE;
        for (Vertex v : vs) {
            if (v.equals(u)) {
                continue;
            }
            double curDist = Vertex.dist(u, v);
            if (curDist < dist) {
                dist = curDist;
                nearest = v;
            }
        }
        return nearest;
    }

    public static boolean admissible(Vertex v, Vertex u, Vertex vv, Vertex uu, double eps) {
        return Vertex.dist(u, v) <= eps * Math.min(Vertex.dist(u, uu), Vertex.dist(v, vv));
    }

    public double x, y;
    public int ind;

    public Vertex(double X, double Y, int Ind) {
        this.x = X;
        this.y = Y;
        this.ind = Ind;
    }

    public boolean equals(Vertex other) {
        return this.ind == other.ind;
    }
}
