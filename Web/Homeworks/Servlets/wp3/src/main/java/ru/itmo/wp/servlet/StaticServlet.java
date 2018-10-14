package ru.itmo.wp.servlet;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sound.midi.SysexMessage;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;

public class StaticServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String[] uries = request.getRequestURI().split("\\+");
        OutputStream outputStream = response.getOutputStream();
        response.setContentType(getContentTypeFromName(uries[0]));

        for (String uri : uries) {
            if (!uri.startsWith("/"))
                uri = "/" + uri;

            File file = new File(System.getProperty("user.dir") + "/src/main/webapp/static" + uri);

            if (file.isFile()) {
                Files.copy(file.toPath(), outputStream);
            } else {
                file = new File(getServletContext().getRealPath("/static" + uri));
                if (file.isFile()) {
                    Files.copy(file.toPath(), outputStream);
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND);
                }
            }
            outputStream.flush();
        }
    }

    private String getContentTypeFromName(String name) {
        name = name.toLowerCase();

        if (name.endsWith(".png")) {
            return "image/png";
        }

        if (name.endsWith(".jpg")) {
            return "image/jpeg";
        }

        if (name.endsWith(".html")) {
            return "text/html";
        }

        if (name.endsWith(".css")) {
            return "text/css";
        }

        if (name.endsWith(".js")) {
            return "application/javascript";
        }

        throw new IllegalArgumentException("Can't find content type for '" + name + "'.");
    }
}
