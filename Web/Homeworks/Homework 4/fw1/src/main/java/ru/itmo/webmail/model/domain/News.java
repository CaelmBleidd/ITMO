package ru.itmo.webmail.model.domain;

import java.io.Serializable;

public class News implements Serializable {
    private long userId;
    private String text;

    public News(User user, String newsText) {
        userId = user.getId();
        text = newsText;
    }

    public long getUserId() {
        return userId;
    }

    public String getText() {
        return text;
    }

    public void setUserId(long userId) {
        this.userId = userId;
    }

    public void setText(String text) {
        this.text = text;
    }
}
