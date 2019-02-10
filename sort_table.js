$(document).ready(function()
{
    var table_index = {
        watched: 0,
        title: 1,
        director: 2,
        year: 3
    };

    var sort_index = 0;
    var lever = 0;
    var sort_increasing = 0;
    var sort_decreasing = 1;
    var tbody = $("tbody").children().get();
    var table_headers = $("thead").children();

    for (var k = 0; k < table_headers.length; k++)
    {
        $("#" + table_headers[k].id).bind("click", function(e)
        {
            lever = (lever + 1) % 2;
            sort_index = table_index[e.target.id];
            switch (sort_index)
            {
            // Alphabetic sort
            case 0:
            case 1:
            case 2:
                tbody.sort(function(a, b) {
                    var l = $(a).children().eq(sort_index).text();
                    var r = $(b).children().eq(sort_index).text();
                    switch (lever)
                    {
                    case sort_decreasing:
                        if (r.toLowerCase() < l.toLowerCase())
                            return 1;
                        else if (r.toLowerCase() > l.toLowerCase())
                            return -1;
                        else
                            return 0;
                    case sort_increasing:
                        if (r.toLowerCase() < l.toLowerCase())
                            return -1;
                        else if (r.toLowerCase() > l.toLowerCase())
                            return 1;
                        else
                            return 0;
                    }
                });
                break;
            // Numeric sort
            case 3:
                tbody.sort(function(a, b) {
                    var l = $(a).children().eq(sort_index).text();
                    var r = $(b).children().eq(sort_index).text();
                    switch (lever)
                    {
                    case sort_decreasing:
                        return l - r;
                    case sort_increasing:
                        return r - l;
                    }
                });
                break;
            }
            $("tbody").children().detach();
            $("tbody").append(tbody);
        });
    }
});
