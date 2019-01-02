import java.io.*
import java.util.StringTokenizer


class Period {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter


    fun solve() {
        val line = reader.next()
        val prefixArray = line.buildPrefixFunction()
        if (line.length % (line.length - prefixArray[line.lastIndex]) == 0)
            print(line.length - prefixArray[line.lastIndex])
        else
            print(line.length)

    }

    fun run() {
        reader = FastScanner(File("input" + ".in"))
        writer = PrintWriter(File("output" + ".out"))

        solve()

        writer.close()
    }

    fun String.buildPrefixFunction(): MutableList<Int> {
        val prefixFunctionArray = MutableList(length) { 0 }
        prefixFunctionArray[0] = 0
        for (i in 1 until length) {
            var k = prefixFunctionArray[i - 1]
            while (k > 0 && this[i] != this[k])
                k = prefixFunctionArray[k - 1]
            if (this[i] == this[k])
                ++k
            prefixFunctionArray[i] = k
        }
        return prefixFunctionArray
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
    Period().run()
}