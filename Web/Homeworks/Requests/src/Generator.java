public class Generator {
    public static void main(String[] args) {
        final String firstPart = "curl 'http://1d3p.wp.codeforces.com/new' -H 'Connection: keep-alive' -H 'Cache-Control: max-age=0' -H 'Origin: http://1d3p.wp.codeforces.com' -H 'Upgrade-Insecure-Requests: 1' -H 'Content-Type: application/x-www-form-urlencoded' -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.92 Safari/537.36' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8' -H 'Referer: http://1d3p.wp.codeforces.com/' -H 'Accept-Encoding: gzip, deflate' -H 'Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7' -H 'Cookie: _ym_uid=1519100231757527794; __utmc=71512449; _ym_d=1536086921; __utmz=71512449.1536742040.63.13.utmcsr=assets.codeforces.com|utmccn=(referral)|utmcmd=referral|utmcct=/files/wp2018/; evercookie_cache=kyc6n1fguqjgicn4q8; evercookie_etag=kyc6n1fguqjgicn4q8; evercookie_png=kyc6n1fguqjgicn4q8; _ym_isad=1; 70a7c28f3de=kyc6n1fguqjgicn4q8; __utma=71512449.1370584364.1519100197.1537103715.1537169937.65; __utmt=1; __utmb=71512449.7.10.1537169937; JSESSIONID=30BF20656BA115778F022668865A62AB' -H 'X-Compress: null' --data '_af=34be50b38beccce4&";
        final String secondPart = "proof=";
        final String thirdPart = "&amount=";
        final String fourthPart = "&submit=Submit' --compressed";
        int proof, amount;

        for (int i = 1; i <= 100; ++i) {
            proof = (int) Math.pow(i, 2);
            amount = i;
            System.out.println(firstPart + secondPart + Integer.toString(proof) + thirdPart + Integer.toString(amount) + fourthPart);
        }
    }
}

