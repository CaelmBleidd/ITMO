import java.io.*
import java.util.StringTokenizer
import kotlin.random.Random.Default.nextInt


class ManySubstrings {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter

    fun solve() {
        val count = reader.nextInt()
        val lines = mutableListOf<String>()
        for (i in 0 until count) {
            lines.add(reader.next())
        }
        val template = reader.next()
        lateinit var automaton: SuffixAutomaton

        measureTime("Create automaton") {
            automaton = SuffixAutomaton(template.length)
        }

        measureTime("Build automaton") {
            automaton.buildAutomaton(template)
        }


        val answers = mutableListOf<String>()

        measureTime("Find answers") {
            for (line in lines) {
                if (automaton.accepts(line))
                    answers.add("YES")
                else
                    answers.add("NO")
            }
        }

        measureTime("Answer") {
            writer.write(answers.joinToString("\n"))
        }
    }

    fun run() {
        writer = PrintWriter(File("search4" + ".in"))
        val upper = "abcsefghijklmnopqrstuvwxyz"
        writer.write("0\n")
        for (i in 0 until 10000)
            writer.write(upper[Math.abs(nextInt()) % 26].toString())
        writer.close()

        reader = FastScanner(File("search4" + ".in"))
        writer = PrintWriter(File("search4" + ".out"))

        solve()

        writer.close()
    }

    fun measureTime(executing: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println(executing + ": run for ${(System.nanoTime() - start) / 10e9}")
    }

    inner class FastScanner(file: File) {
        var br: BufferedReader = BufferedReader(FileReader(file))
        var st: StringTokenizer? = null

        fun next(): String {
            while (st == null || !st!!.hasMoreTokens()) {
                st = StringTokenizer(br.readLine())
            }
            return st!!.nextToken()
        }

        fun nextInt(): Int {
            return next().toInt()
        }

        fun nextLong(): Long {
            return next().toLong()
        }

        fun nextDouble(): Double {
            return next().toDouble()
        }
    }

    class SuffixAutomaton(maxSize: Int) {
            var states = MutableList(maxSize * 2) { State() }
            var size = 0
            var last = 0

            init {
                states[0].length = 0
                states[0].link = -1
                size++
            }

            fun addSymbol(symbol: Char) {
                val cur = size++
                states[cur].length = states[last].length + 1
                var p = last
                while (p != -1 && !states[p].next.containsKey(symbol)) {
                    states[p].next[symbol] = cur
                    p = states[p].link
                }
                if (p == -1)
                    states[cur].link = 0
                else {
                    val q = states[p].next[symbol]!!
                    if (states[p].length + 1 == states[q].length)
                        states[cur].link = q
                    else {
                        val clone = size++
                        states[clone].length = states[p].length + 1
                        states[clone].next.putAll(states[q].next)
                        states[clone].link = states[q].link
                        while (p != -1 && states[p].next[symbol] == q) {
    //                        states[p].next.remove(symbol)
                            states[p].next[symbol] = clone
                            p = states[p].link
                        }
                        states[cur].link = clone
                        states[q].link = clone
                    }
                }
                last = cur
            }

            fun buildAutomaton(line: String) {
                for (symbol in line) {
                    addSymbol(symbol)
                }
            }

            fun accepts(line: String): Boolean {
                var actualState = states[0]
                for (symbol in line) {
                    if (actualState.next.containsKey(symbol))
                        actualState = states[actualState.next[symbol]!!]
                    else
                        return false
                }
                return true
            }

            data class State(var length: Int = 0, var link: Int = -2, var next: HashMap<Char, Int> = hashMapOf())
        }
}

fun main(args: Array<String>) {
    ManySubstrings().run()
}
