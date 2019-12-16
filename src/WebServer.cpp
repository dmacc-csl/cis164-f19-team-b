#include <iostream>
#include <string>
#include <vector>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/URI.h>
#include "WebServer.h"

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;
using Poco::URI;

//
class MyRequestHandler : public HTTPRequestHandler
{
public:
    virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
    {
        string dbfile = "dashboards.db";
        Poco::Data::SQLite::Connector::registerConnector();
        Database database(dbfile);
        
        std::vector<Dashboard> dashboards = database.getAllDashboards();
        
        resp.setStatus(HTTPResponse::HTTP_OK);
        resp.setContentType("text/html");
        
        std::vector<string> segments;
        URI uri(req.getURI());
        uri.getPathSegments(segments);
        
        /*
         with two parameters, a dashboard has been selected, so display its tiles
         */
        int selDbId = 0, selDbIdx = 0;
        
        if ( uri.getQueryParameters().size() == 2 ) {
            selDbId = stoi(uri.getQueryParameters()[1].second);
            cout << "dashboardId selected=" + uri.getQueryParameters()[1].second;
        
            // find index of dashboard Id matching selection parameter
            for( int i=0; i < dashboards.size(); i++) {
                if ( dashboards[i].getId() == selDbId )
                    selDbIdx = i;
            }
        }

        ostream& out = resp.send();
        out <<
        "<h1>Weather Dashboard Viewer</h1>"
        "<form action=\".\" method=\"get\" target=\"_top\">"
            "<input type=\"hidden\" name=\"formName\" value=\"selectView\" />"
            "<label for=\"dashboard\">Select dashboard:</label>"
        "<select name=\"dashboard\" id=\"selDashboard\">";
        
        for (int i=0; i<dashboards.size(); i++) {
            out << "<option value=\"" << dashboards[i].getId() <<  "\"";
            
            // set selected dashboard option
                if ( i == selDbIdx )
                    out << " selected ";
            out << ">" <<   dashboards[i].getName() << "</option>";
        }
            out << "</select>"
                "<input type=\"submit\" value=\"Go\" class=\"button\" /></form>";
        
        out <<
            "<form action=\".\" method=\"get\" target=\"_top\">"
            "<input type=\"text\" name=\"dashboardName\" id=\"dashboardName\" />"
            "<input type=\"submit\" value=\"Save/Add\" class=\"button\" /><br><br>";
        ;
        
        // draw all tiles for selected dashboard
        for (int i=0; i < dashboards[selDbIdx].getTiles().size(); i++)
            out << drawTile(dashboards[selDbIdx].getTiles()[i], i);
        
        out << "</form>";
        
        out.flush();

/*
        cout << endl
        << "Response sent for count=" << count++
        << " and URI=" << req.getURI() << endl
        << " and query=" << uri.getQuery() << endl
        << " and param count=" << uri.getQueryParameters().size() << endl;
*/
 
    }
    
    string drawTile (Tile& tile, int tCount) {
        //tCount is used as a suffix for field identifiers
        string idSuffix = to_string(tCount);

        string floatStyle = " style='float:left;' ";
        if (tCount % 2 == 0)
            string floatright = " style='float:right;' ";

        string code = "<div class='tile'" + floatStyle + "><div style='border: 1px black solid;";
        code += "width: 200px; height: 90px;'><span style='margin:8px 8px;'>";
        
        // get results of API call
        code += "api result";              /* callApi(tile) */
        code += "</span></div><br>";
        // end of api results view
        
        //location field
        string fieldID = "loc" + idSuffix;
        code += "<label for \"" + fieldID + "\">Location</label>";
        code += "<input type=\"text\" name=\"" + fieldID + "\" id=\"" + fieldID + "\" ";
        code += "value=\"" + tile.getCity().getName() + ", " + "\" /><br>";
        
    /*
        <label for="name">Name</label>
        <input type="text" name="name" id="name" class="text" value="anonymous" />
    */
        
        // weatherview selection
        code += "<label for 'wv" + idSuffix + "'>View</label>";
        code += "<select name='wv" + idSuffix + "' id='wv" + idSuffix + "'>";
        
/*
            it would be handy to have getWeatherview(int id) method in order to more
            easily cycle through the views, expecially if new views are ever added. In
            lieu I'll use this string array.
*/
        string wvname[4] { "", "Current", "5 day forecast", "UV Index"};
        
        //add options for select tag
        for (int i=1; i<4; i++) {
            code += "<option value=\""+ to_string(i) + "\" ";
            
            //set selected item
            if ( i == tile.getWeatherview().getId() )
                code += " selected ";
            
            code += ">" + wvname[i] + "</option>";
        }
        
        code += "</select><br><br>";
        
        // add
        
        code += "</div>";
        return code;
    }
    
private:
    static int count;
};

int MyRequestHandler::count = 0;

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
    {
        return new MyRequestHandler;
    }
};

class MyServerApp : public ServerApplication
{
protected:
    int main(const vector<string> &)
    {
        HTTPServer s(new MyRequestHandlerFactory, ServerSocket(9090), new HTTPServerParams);
        
        s.start();
        cout << endl << "Server started" << endl;
        
        waitForTerminationRequest();  // wait for CTRL-C or kill
        
        cout << endl << "Shutting down..." << endl;
        s.stop();
        
        return Application::EXIT_OK;
    }
};


/**************** for reals *******************/
            int main(int argc, char** argv)
            {
                MyServerApp app;
                return app.run(argc, argv);
            }

