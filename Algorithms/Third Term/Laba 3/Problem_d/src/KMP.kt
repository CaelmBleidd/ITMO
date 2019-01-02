import java.io.*
import java.util.StringTokenizer


class KMP {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter


    fun solve() {
        val pattern = reader.next()
        val template = reader.next()
        val line = "$pattern~$template"
        val prefixFunctionArray = buildPrefixFunction(line)
        val answer = mutableListOf<Int>()
        for (i in 0 until template.length) {
            if (prefixFunctionArray[pattern.length + i + 1] == pattern.length) {
                answer.add(i - pattern.length + 2)
            }
        }
        println(answer.size)
        print(answer.joinToString(" "))

    }

    fun buildPrefixFunction(line: String): MutableList<Int> {
        val prefixFunctionArray = MutableList(line.length) { 0 }
        prefixFunctionArray[0] = 0
        for (i in 1 until line.length) {
            var k = prefixFunctionArray[i - 1]
            while (k > 0 && line[i] != line[k])
                k = prefixFunctionArray[k - 1]
            if (line[i] == line[k])
                ++k
            prefixFunctionArray[i] = k
        }
        return prefixFunctionArray
    }

    fun run() {
        reader = FastScanner(File("input" + ".in"))
        writer = PrintWriter(File("output" + ".out"))

        solve()

        writer.close()
    }

    fun measureTime(executing: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println(executing + ": run for ${(System.nanoTime() - start) / 10e9}")
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
    KMP().run()
}