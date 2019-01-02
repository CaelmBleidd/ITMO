<#import "common.ftl" as c>

<@c.page>
    <form method="post" action="/addNews" id="submit-news-form">
        <input type="hidden" name="action" value="submitNews">
        <label for="news-text">News Text</label>
        <textarea name="news-text" form="submit-news-form" title="News Text">Enter news text here...</textarea>
        <input type="submit" value="Submit">
    </form>
</@c.page>
