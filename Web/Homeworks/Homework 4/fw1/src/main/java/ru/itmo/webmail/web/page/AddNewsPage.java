package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import java.util.Objects;

public class AddNewsPage extends Page {
    private void submitNews(HttpServletRequest request) throws ServletException {
        User user = (User) request.getSession().getAttribute("AuthorizedUser");
        if (user == null) {
            throw new ServletException("Can't submit news unauthorized");
        }
        String newsText = request.getParameter("news-text");
        Objects.requireNonNull(newsText);
        newsService.create(user, newsText);

        throw new RedirectException("/index", "newsSubmitted");
    }

    private void action() {
        //no action
    }
}
