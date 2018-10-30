package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.service.UserService;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class UsersPage {
    private UserService userService = new UserService();

    private void action(HttpServletRequest request, Map<String, Object> view) {
        view.put("users", userService.findAll());
    }
}
