package ru.itmo.webmail.web.page;

import java.util.Map;

public class UsersPage extends Page {
    private void action(Map<String, Object> view) {
        view.put("users", userService.findAll());
    }
}
