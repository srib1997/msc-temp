exports.up = async (knex) => {
  await knex.raw('CREATE EXTENSION IF NOT EXISTS "uuid-ossp";')

  await knex.schema.createTable('uv_sensor', function (table) {
    table.uuid('id').defaultTo(knex.raw('uuid_generate_v4()')).primary()
    table.timestamp('created_at').defaultTo(knex.raw('now()')).notNullable()
    table.string('data')
  })

  await knex.schema.createTable('temp_sensor', function (table) {
    table.uuid('id').defaultTo(knex.raw('uuid_generate_v4()')).primary()
    table.timestamp('created_at').defaultTo(knex.raw('now()')).notNullable()
    table.string('celsius')
  })

  await knex.schema.createTable('humidity_sensor', function (table) {
    table.uuid('id').defaultTo(knex.raw('uuid_generate_v4()')).primary()
    table.timestamp('created_at').defaultTo(knex.raw('now()')).notNullable()
    table.string('data')
  })

  await knex.schema.createTable('wind_sensor', function (table) {
    table.uuid('id').defaultTo(knex.raw('uuid_generate_v4()')).primary()
    table.timestamp('created_at').defaultTo(knex.raw('now()')).notNullable()
    table.string('meter_second')
  })
}

exports.down = async (knex) => {
  await knex.schema.dropTableIfExists('uv_sensor')
  await knex.schema.dropTableIfExists('temp_sensor')
  await knex.schema.dropTableIfExists('humidity_sensor')
  await knex.schema.dropTableIfExists('wind_sensor')
}
