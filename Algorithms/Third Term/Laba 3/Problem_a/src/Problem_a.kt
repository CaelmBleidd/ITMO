import java.io.*
import java.util.StringTokenizer


class ProblemA {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter

    private val primeNumber = 31L
    private val degrees = arrayListOf(1L)
    private val prefixArray = arrayListOf(0L)


    private fun solve() {

        val line = reader.next()
        val m = reader.nextInt()
        val answer = mutableListOf<String>()

        calculatePrefixHashes(line)

        for (i in 0 until m) {
            val a = reader.nextInt() - 1
            val b = reader.nextInt() - 1
            val c = reader.nextInt() - 1
            val d = reader.nextInt() - 1

            if (a - b != c - d) {
                answer.add("No")
                continue
            }

            if (a == c && b == d) {
                answer.add("Yes")
                continue
            }

            var firstHash = prefixArray[b]
            var secondHash = prefixArray[d]
            if (a != 0)
                firstHash -= prefixArray[a - 1]
            if (c != 0)
                secondHash -= prefixArray[c - 1]


            if (a < c && firstHash * degrees[c - a] == secondHash || a > c && firstHash == secondHash * degrees[a - c]) {
                answer.add("Yes")
            } else {
                answer.add("No")
            }
        }

        print(answer.joinToString("\n"))
    }

    private fun calculateDegrees(line: String) {
        for (i in 1..line.length) {
            degrees.add(degrees[i - 1] * primeNumber)
        }
    }

    private fun calculatePrefixHashes(line: String) {
        calculateDegrees(line)
        prefixArray[0] = (line[0] - 'a' + 1) * degrees[0]
        for (i in 1..line.lastIndex) {
            prefixArray.add(prefixArray[i - 1] + (line[i] - 'a' + 1) * degrees[i])
        }
    }

    fun run() {
        reader = FastScanner(File("input" + ".in"))
        writer = PrintWriter(File("output" + ".out"))

        solve()

        writer.close()
    }

    fun measureTime(name: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println("Problem_a: run for ${(System.nanoTime() - start) / 10e9}")
    }


    inner class FastScanner(file: File) {
        var br: BufferedReader = BufferedReader(InputStreamReader(System.`in`))
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
}

fun main(args: Array<String>) {
    ProblemA().run()
}