package ru.itmo.webmail.web.page;

import ru.itmo.webmail.ServletUtils;
import ru.itmo.webmail.web.exception.AuthorizationException;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class EnterPage extends Page {
    private void enter(HttpServletRequest request, Map<String, Object> view) {
        String login = request.getParameter("login");
        String password = request.getParameter("password");

        try {
            ServletUtils.doAuthorization(userService, login, password, request, view);
            throw new RedirectException("/index", "authorizationDone");
        } catch (AuthorizationException e) {
            view.put("login", login);
            view.put("password", password);
            view.put("error", e.getMessage());
        }
    }

    private void action() {
        // No operations.
    }
}
