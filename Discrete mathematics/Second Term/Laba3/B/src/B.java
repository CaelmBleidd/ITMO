import java.io.*;
import java.util.*;


public class B {
    class Pair {
        String from = "", to = "";
        Pair(String from, String to) {
            this.from = from;
            this.to = to;
        }
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public static void main(String[] args) throws IOException {
        new B().run();
    }

    public void solve() throws IOException {
        int n = nextInt();
        String start = nextToken();
        Pair[] rules = new Pair[n + 1];
        for (int i = 1; i < n + 1; i++) {
            String[] line = br.readLine().split(" ");
            if (line.length > 2)
                rules[i] = new Pair(line[0], line[2]);
            else
                rules[i] = new Pair(line[0], "");
        }
        HashSet<String> epsilons = new HashSet<>();
        for (int i = 1; i < n + 1; i++) {
            if (rules[i].to.equals("")) {
                epsilons.add(rules[i].from);
            }
        }

        boolean was_changed = true;
        while (was_changed) {
            was_changed = false;
            for (int i = 1; i < n + 1; i++) {
                boolean is_epsilon = true;
                for (int p = 0; p < rules[i].to.length(); p++) {
                    String symbol = rules[i].to.substring(p, p + 1);
                    if (!epsilons.contains(symbol)) {
                        is_epsilon = false;
                        break;
                    }
                }
                if (is_epsilon) {
                    if (!epsilons.contains(rules[i].from)) {
                        epsilons.add(rules[i].from);
                        was_changed = true;
                    } else
                        continue;
                }
            }
        }

        Object[] output = epsilons.toArray();
        Arrays.sort(output);
        for (Object s : output) {
            out.print(s + "\n");
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("epsilon.in"));
            out = new PrintWriter("epsilon.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
