import java.io.*;
import java.util.*;


public class C {
    class Pair {
        String from = "", to = "";

        Pair(String from, String to) {
            this.from = from;
            this.to = to;
        }
    }

    boolean GLOBAL_CHANGE = true;
    boolean ONE_MORE_CHANGE = true;
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
        new C().run();
    }

    public void solve() throws IOException {
        HashSet<String> alphabet = new HashSet<>();

        int n = nextInt();
        String start = nextToken();
        Pair[] rules = new Pair[n + 1];

        HashMap<String, HashSet<String>> rulesssssss = new HashMap<>();
        HashSet<String> generating = new HashSet<>();
        HashSet<String> reachable = new HashSet<>();
int count = 100;

        for (int i = 1; i < n + 1; i++) {
            String[] line = br.readLine().split(" ");
            alphabet.add(line[0]);
            if (line.length > 2) {
                rules[i] = new Pair(line[0], line[2]);
                HashSet<String> tmp = rulesssssss.get(line[0]);
                if (tmp != null) {
                    tmp.add(line[2]);
                } else {
                    tmp = new HashSet<String>();
                    tmp.add(line[2]);
                }
                rulesssssss.put(line[0], tmp);
                for (int p = 0; p < line[2].length(); p++) {
                    if (Character.isUpperCase(line[2].charAt(p)))
                        alphabet.add(line[2].substring(p, p + 1));
                }
            } else {
                HashSet<String> tmp = rulesssssss.get(line[0]);
                if (tmp != null) {
                    tmp.add("");
                } else {
                    tmp = new HashSet<>();
                    tmp.add("");
                }
                rulesssssss.put(line[0], tmp);
                rules[i] = new Pair(line[0], "");
            }
        }
        boolean was_changed;

        while (ONE_MORE_CHANGE) {
            ONE_MORE_CHANGE = false;
            if (GLOBAL_CHANGE) {
                GLOBAL_CHANGE = false;
                for (int i = 1; i < n + 1; i++) {
                    boolean is_ok = true;
                    for (int p = 0; p < rules[i].to.length(); p++) {
                        char symbol = rules[i].to.charAt(p);
                        if (Character.isUpperCase(symbol)) {
                            is_ok = false;
                            break;
                        }
                    }
                    if (is_ok)
                        generating.add(rules[i].from);
                }

                was_changed = true;
                while (was_changed) {
                    was_changed = false;
                    for (int i = 1; i < n + 1; i++) {
                        boolean is_gen = true;
                        for (int p = 0; p < rules[i].to.length(); p++) {
                            String symbol = rules[i].to.substring(p, p + 1);
                            if (!generating.contains(symbol) && Character.isUpperCase(symbol.charAt(0))) {
                                is_gen = false;
                                break;
                            }
                        }
                        if (is_gen) {
                            if (!generating.contains(rules[i].from)) {
                                generating.add(rules[i].from);
                                was_changed = true;
                            }
                        }
                    }
                }

//// нужно избавиться от лишних правил
//        for (int i = 1; i < n + 1; i++) {
//            for (int p = 0; p < rules[i].to.length(); p++) {
//                if ()
//            }
//        }
//


                was_changed = true;
                while (was_changed) {
                    was_changed = false;
                    for (int i = 1; i < n + 1; i++) {
                        for (int p = 0; p < rules[i].to.length(); p++) {
                            String symbol = rules[i].to.substring(p, p + 1);
                            if (generating.contains(symbol) && !generating.contains(rules[i].from)) {
                                generating.remove(symbol);
                                was_changed = true;
                            }
                        }
                        if (!generating.contains(rules[i].from)) {
                            for (int p = 0; p < rules[i].to.length(); p++) {
                                String symbol = rules[i].to.substring(p, p + 1);
                                if (generating.contains(symbol)) {
                                    generating.remove(symbol);
                                    was_changed = true;
                                }
                            }
                        }
                    }
                }


                was_changed = true;
                while (was_changed) {
                    was_changed = false;
                    Pair[] tmp = new Pair[n + 1];
                    int new_n = 1;
                    for (int i = 1; i < n + 1; i++) {
                        boolean is_ok = true;
                        for (int p = 0; p < rules[i].to.length(); p++) {
                            if (!generating.contains(rules[i].to.substring(p, p + 1)) && Character.isUpperCase(rules[i].to.charAt(p))) {
                                is_ok = false;
                                was_changed = true;
                                break;
                            }
                        }
                        if (!generating.contains(rules[i].from)) {
                            is_ok = false;
                            was_changed = true;
                        }
                        if (is_ok) {
                            tmp[new_n++] = rules[i];
                        }
                    }
                    if (rules.length != tmp.length) {
                        GLOBAL_CHANGE = true;
                    }
                    rules = tmp;
                    n = new_n - 1;


                } // должны остаться только "хорошие" правила, но чот хз

            }

            GLOBAL_CHANGE = true;
            while (GLOBAL_CHANGE) {
                GLOBAL_CHANGE = false;
                reachable.add(start);
                was_changed = true;
                while (was_changed) {
                    was_changed = false;
                    for (int i = 1; i < n + 1; i++) {
                        if (reachable.contains(rules[i].from)) {
                            for (int p = 0; p < rules[i].to.length(); p++) {
                                if (!reachable.contains(rules[i].to.substring(p, p + 1)) && Character.isUpperCase(rules[i].to.charAt(p))) {
                                    was_changed = true;
                                    reachable.add(rules[i].to.substring(p, p + 1));
                                }
                            }
                        }
                    }
                }

                was_changed = true;
                while (was_changed) {
                    was_changed = false;
                    Pair[] tmp = new Pair[n + 1];
                    int new_n = 1;
                    for (int i = 1; i < n + 1; i++) {
                        boolean is_ok = true;
                        for (int p = 0; p < rules[i].to.length(); p++) {
                            if (!reachable.contains(rules[i].from)) {
                                is_ok = false;
                                was_changed = true;
                                break;
                            }
                        }
                        if (is_ok) {
                            tmp[new_n++] = rules[i];
                        }
                    }
                    if (rules.length != tmp.length) {
                        GLOBAL_CHANGE = true;
                    }
                    rules = tmp;
                    n = new_n - 1;
                }
            }
            if (count-- != 0)
                ONE_MORE_CHANGE = true;
        }
        HashSet<String> output = new HashSet<>();

        for (String s : alphabet) {
            if (!generating.contains(s) || !reachable.contains(s)) {
                output.add(s);
            }
        }

        Object[] answer = output.toArray();
        Arrays.sort(answer);
        for (Object s : answer) {
            out.print(s + " ");
        }

    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("useless.in"));
            out = new PrintWriter("useless.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}