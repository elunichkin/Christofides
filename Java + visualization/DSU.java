public class DSU {
    private int num;
    private int[] parent;
    private int[] size;

    public DSU(int n) {
        this.num = n;
        parent = new int[num];
        size = new int[num];
        for (int i = 0; i < num; ++i) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    public int find(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    public void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) {
                parent[a] = b;
                size[b] += size[a];
            }
            else {
                parent[b] = a;
                size[a] += size[b];
            }
        }
    }
}
