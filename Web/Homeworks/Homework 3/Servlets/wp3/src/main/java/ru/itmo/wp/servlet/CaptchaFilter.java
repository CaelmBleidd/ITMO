package ru.itmo.wp.servlet;

import ru.itmo.wp.util.ImageUtils;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Base64;
import java.util.concurrent.ThreadLocalRandom;

public class CaptchaFilter extends HttpFilter {
    @Override
    protected void doFilter(HttpServletRequest request, HttpServletResponse response, FilterChain chain) throws IOException, ServletException {
        if (checkIfNonGet(request)
                || checkIfFavicon(request)
                || checkIfPassedCaptcha(request)
                || checkIfCorrectAnswer(request)) {
            chain.doFilter(request, response);
            return;
        }

        String captchaText = generateCaptchaText();
        request.getSession().setAttribute("Expected-Answer", captchaText);
        sendCaptchaPage(response, captchaText);
    }

    private boolean checkIfNonGet(HttpServletRequest request) {
        return !request.getMethod().equalsIgnoreCase("GET");
    }

    private boolean checkIfFavicon(HttpServletRequest request) {
        return request.getRequestURI().endsWith("favicon.ico");
    }

    private boolean checkIfPassedCaptcha(HttpServletRequest request) {
        Boolean captchaPassed = (Boolean) request.getSession().getAttribute("Captcha-Passed");
        return captchaPassed != null && captchaPassed;
    }

    private boolean checkIfCorrectAnswer(HttpServletRequest request) {
        String actualAnswer = request.getParameter("answer");
        if (actualAnswer != null) {
            String expectedAnswer = (String) request.getSession().getAttribute("Expected-Answer");
            if (actualAnswer.equals(expectedAnswer)) {
                request.getSession().setAttribute("Captcha-Passed", true);
                return true;
            }
        }
        return false;
    }

    private String generateCaptchaText() {
        return String.valueOf(ThreadLocalRandom.current().nextInt(100, 1000));
    }

    private void sendCaptchaPage(HttpServletResponse response, String captchaText) throws IOException {
        response.setContentType("text/html");
        ServletOutputStream outputStream = response.getOutputStream();
        outputStream.print(makeImageTag(captchaText));
        Path captchaFormPath = Paths.get(getServletContext().getRealPath("static"), "captcha.html");
        Files.copy(captchaFormPath, outputStream);
        outputStream.flush();
    }

    private String makeImageTag(String captchaText) {
        byte[] imageBytes = ImageUtils.toPng(captchaText);
        String base64String = Base64.getEncoder().encodeToString(imageBytes);
        return String.format("<img src=\"data:image/png;base64,%s\">\n", base64String);
    }
}
