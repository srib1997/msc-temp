// Update with your config settings.
// https://medium.com/@Umesh_Kafle/postgresql-and-postgis-installation-in-mac-os-87fa98a6814d
module.exports = {

  development: {
    client: 'pg',
    connection: {
      host: 'localhost',
      database: 'msc_temp',
      user: '',
      password: ''
    },
    pool: {
      min: 2,
      max: 10
    },
    migrations: {
      directory: './knex/migrations'
    },
    seeds: {
      directory: './knex/seeds'
    }
  },

}
