package ru.itmo.wm4.form;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.Size;

public class NoticeForm {

    @NotEmpty
    @Size(min = 10, message = "too small notice, let it grow up")
    private String text;

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }
}
