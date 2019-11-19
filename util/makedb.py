import json
import sqlite3

db_file = 'dashboards.db'
city_json = 'city.list.json'
view_json = 'view.list.json'

with sqlite3.connect(db_file) as connection:
    connection.execute("""CREATE TABLE IF NOT EXISTS dashboard (
                            dashboard_id INTEGER NOT NULL PRIMARY KEY,
                            name         TEXT    NOT NULL
                    )""")
    connection.execute("""CREATE TABLE IF NOT EXISTS weatherview (
                            weatherview_id INTEGER NOT NULL PRIMARY KEY,
                            name           TEXT    NOT NULL,
                            description    TEXT    NOT NULL,
                            call_string    TEXT    NOT NULL
                    )""")
    connection.execute("""CREATE TABLE IF NOT EXISTS city (
                            city_id INTEGER NOT NULL PRIMARY KEY,
                            name    TEXT    NOT NULL,
                            country TEXT    NOT NULL,
                            lon     DOUBLE  NOT NULL,
                            lat     DOUBLE  NOT NULL
                    )""")
    connection.execute("""CREATE TABLE IF NOT EXISTS tile (
                            tile_id        INTEGER NOT NULL PRIMARY KEY,
                            weatherview_id INTEGER NOT NULL,
                            city_id        INTEGER NOT NULL,
                            dashboard_id   INTEGER NOT NULL,
                            FOREIGN KEY(weatherview_id) REFERENCES view(weatherview_id),
                            FOREIGN KEY(city_id) REFERENCES city(city_id),
                            FOREIGN KEY(dashboard_id) REFERENCES dashboard(dashboard_id)
                    )""")

    with open(city_json) as json_file:
        data = json.load(json_file)
        for c in data:
            city_id = str(c['id'])
            name = c['name'].replace("'", "")
            country = c['country']
            lon = str(c['coord']['lon'])
            lat = str(c['coord']['lat'])

            connection.execute("""INSERT OR REPLACE INTO city (
                                    city_id, name, country, lon, lat
                                ) VALUES (""" +
                            "'" + city_id + "', " +
                            "'" + name + "', " +
                            "'" + country + "', " +
                            "'" + lon + "', " +
                            "'" + lat + "')")

    with open(view_json) as json_file:
        data = json.load(json_file)
        for v in data:
            weatherview_id = str(v['id'])
            name = v['name']
            description = v['description']
            call_string = v['call_string']

            connection.execute("""INSERT OR REPLACE INTO weatherview (
                                    weatherview_id, name, description, call_string
                                ) VALUES (""" +
                            "'" + weatherview_id + "', " +
                            "'" + name + "', " +
                            "'" + description + "', " +
                            "'" + call_string + "')")


