package ru.itmo.wp.servlet;

import com.google.gson.Gson;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MessagesServlet extends HttpServlet {
    private final static Gson gson = new Gson();
    private final List<Message> messages = new ArrayList<>();

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");

        String uri = request.getRequestURI();

        String[] uriParts = uri.split("/");

        if (uriParts.length != 3) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }
        String action = uriParts[2];

        String json;
        switch (action) {
            case "auth":
                json = processAuth(request);
                break;
            case "findAll":
                json = processFindAll();
                break;
            case "add":
                json = processAdd(request);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
                return;
        }
        response.getWriter().print(json);
        response.getWriter().flush();
    }

    private String processAuth(HttpServletRequest request) {
        String userName = request.getParameter("user");
        if (userName == null) {
            userName = "";
        } else {
            request.getSession().setAttribute("user", userName);
        }
        return convertToJson(userName);
    }
    
    private String processFindAll() {
        return convertToJson(messages);
    }

    private String processAdd(HttpServletRequest request) {
        String userName = (String) request.getSession().getAttribute("user");
        String text = request.getParameter("text");

        messages.add(new Message(userName, text));
        return convertToJson("");
    }

    
    private String convertToJson(Object object) {
        return gson.toJson(object);
    }

    private class Message {
        private String user;
        private String text;

        Message(String user, String text) {
            this.user = user;
            this.text = text;
        }
    }
}
