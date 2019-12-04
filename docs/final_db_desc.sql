
/*
In this design, tiles are made from a city, a view, and a profile. While each
profile is expected to have exactly 4 tiles, storing the data in this way
allows for greater extensibility and flexibility and eliminates redundancy.
"View" and "city" are validation tables, preventing other application
components from successfully storing profiles that would fail to load.
Furthermore, if changes are made ot the API or our "sensors", the tables can
be updated instead of mending the profiles row by row. While "tile" could be
purely a composite key, I've included a sequenced primary key for ease of
handling elsewhere in the program.
*/

-- boolean insertDashboard(Dashboard &d)
INSERT INTO dashboard (name)
VALUES (d.name);
/*
Presumably a dashboard object will contain an array of tiles and the logic
in the insertDashboard member function would make use of the insertTile function
in addition to doing some input validation.
*/

-- boolean updateDashboard(Dashboard &d)
UPDATE dashboard
   SET name = d.name
 WHERE profile_id = d.id;
/*
Uses a profile object to update a profile in the database. Again, this function
would make use of the updateTile function in addition to updating the profile
table.
*/

-- boolean insertTile(Tile &t, int p)
INSERT INTO tile (profile_id, view_id, city_id)
VALUES (p, t.view.id, t.city.id);
/*
Makes use of the tile member objects to add a tile to the database. This
function does not also insert views and cities because these tables are
predetermined by the sensors "puled from the API" to ensure validity of
tile objects. Since the tile object belongs to a profile object and reciprocal
ownership is messy, the profile_id is passed in by the calling process.
*/

-- boolean updateTile(Tile &t)
UPDATE tile
   SET view_id = t.view.id,
       city_id = t.city.id
 WHERE tile_id = t.id;
/*
Uses a tile object to update a tile in the database. Since there should be no
need to change the profile that a tile object belongs to, the update statement
does not set the value of profile_id.
*/

-- map<int, string> getAllDashboards()
SELECT *
  FROM profile;
/*
Gets all dashboard names and IDs so that a profile can be requested by id.
*/

-- Dashboard getDashboard(int id)
SELECT name
  FROM dashboard
 WHERE dashboard_id = id;
SELECT t.tile_id, v.view_id, v.name, v.description, c.city_id, c.name
  FROM tile t
  JOIN view v
    ON t.view_id = v.view_id
  JOIN city
    ON t.city_id = c.city_id
 WHERE t.dashboard_id = id;
/*
Uses a single result query to get the name of the profile to create the
profile object and then uses a multiple row query to fetch all of the
necessary information to create the member objects. Presumably a Profile
object could be created elsewhere with it's name and passed in to be populated
but this way seemed more conducive to a group project, sacrificing a small
amount of efficiency for a large amount of stability.
*/

-- set<View> getAllViews()
SELECT *
  FROM view;
/*
Providing a set of all available views in the database API allows other
application components to construct valid tiles before attempting to insert
them.
*/

-- City getCity(String n)
SELECT *
  FROM city
WHERE LOWER(n) = LOWER(name);
/*
This gets the necessary information to return a City object by attempting to
match the name value. This assumes that there are no duplicate names in the
city table, which I wouldn't exactly call best practice, but again simplifies
things for collaboration and in this case is probably a pretty safe assumption.
*/

-- map<int, string> getAllCities()
SELECT *
  FROM city;
/*
While it is unlikely that the application interface would have a pulldown menu
with all of the available cities, providing access to a collection through the
database API allows other components of the application to use map member
functions to more efficiently select a valid city without making multiple
calls to getCity.
*/


